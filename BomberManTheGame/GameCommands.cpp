#include "GameCommands.h"

#include "CollisionBoxManager.h"
#include "GoldState.h"
#include "InputManager.h"
#include "ServiceLocator.h"

GameCommands::DiggerMovement::DiggerMovement(dae::GameObject* owner, const glm::vec2& dir, bool digger)
{
	m_pGameObject = owner;
	m_Dir = dir;
    m_pCollision = m_pGameObject->GetComponent<dae::CollisionBoxComponent>();
    m_Digger = digger;
}

void GameCommands::DiggerMovement::Execute(float deltaTime)
{
    if (m_pGameObject->ReturnDeleting()) return;

    glm::vec2 pos = m_pGameObject->GetRelativePosition();

    glm::vec2 upMiddel = { m_pGameObject->GetRelativePosition().x / 2 , m_pGameObject->GetRelativePosition().y };
    glm::vec2 downMiddel = { m_pGameObject->GetRelativePosition().x , m_pGameObject->GetRelativePosition().y + 24 };
    glm::vec2 Leftmiddel = { m_pGameObject->GetRelativePosition().x , m_pGameObject->GetRelativePosition().y + 12 };
    glm::vec2 Rightmiddel = { m_pGameObject->GetRelativePosition().x + 24 , m_pGameObject->GetRelativePosition().y + 12 };

    if (m_Digger) //Single/Coop -> Digger
    {
        auto OverlappedBox = dae::CollisionBoxManager::GetInstance().CheckForCollisionComponent(m_pGameObject->GetComponent<dae::CollisionBoxComponent>());

        if (OverlappedBox != nullptr)
        {
            if (OverlappedBox->GetOwner()->GetTag() == "Break")
            {
                dae::CollisionBoxManager::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::CollisionBoxComponent>());
                dae::CollisionBoxManager::GetInstance().RemoveDirtBox(OverlappedBox->GetOwner()->GetComponent<dae::CollisionBoxComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
            }

            if (OverlappedBox->GetOwner()->GetTag() == "Emerald")
            {
                dae::CollisionBoxManager::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::CollisionBoxComponent>());
                dae::CollisionBoxManager::GetInstance().RemoveEmeraldBox(OverlappedBox->GetOwner()->GetComponent<dae::CollisionBoxComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
            }

            if (OverlappedBox->GetOwner()->GetTag() == "Gold" && OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState())
            {
                dae::CollisionBoxManager::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::CollisionBoxComponent>());
                dae::CollisionBoxManager::GetInstance().RemoveGoldBox(OverlappedBox->GetOwner()->GetComponent<dae::CollisionBoxComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
            }
        }

        if (!dae::CollisionBoxManager::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, false))
            return;
    }
    else //Verus -> Nobbin
    {
        if (!dae::CollisionBoxManager::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, true))
            return;
    }

    pos.x += m_Dir.x * deltaTime;
    pos.y += m_Dir.y * deltaTime;
    
    m_pGameObject->SetRelativePosition(pos);
}


GameCommands::SwitchGameMode::SwitchGameMode(std::shared_ptr<dae::GameObject> owner, dae::GameObject* text, const int& currentScreen, dae::ScreenManager* screen)
	:m_pScreen{owner},
    m_pTextMode{text},
    m_CurrentScreen{ currentScreen },
	m_pScreenManager{ screen }
{
}

void GameCommands::SwitchGameMode::Execute(float)
{
    if (GetKeyPressed()) return;

    std::cout << "Still goes\n";

    auto text = m_pTextMode->GetComponent<dae::TextComponent>();
    //m_pScreenManager->SwitchScreens();
    std::cout << m_CurrentScreen << '\n';

    switch (m_CurrentScreen)
    {
    case 0:
        m_CurrentScreen = 1;
        text->SetText("Coop");
        break;

    case 1:
        m_CurrentScreen = 2;
        text->SetText("Versus");
        break;

    case 2:
        m_CurrentScreen = 0;
        text->SetText("Single");
        break;
    }

    m_pScreenManager->SetCurrentEnum(m_CurrentScreen);

    SetKeyPressed(true);
}

GameCommands::AcceptGameMode::AcceptGameMode(std::shared_ptr<dae::GameObject> owner, dae::ScreenManager* screen)
	:m_pScreen{owner},
	m_pScreenManager{screen}
{
}

void GameCommands::AcceptGameMode::Execute(float)
{
    //if (m_Pressed) return;
    if (GetKeyPressed()) return;


    if(m_pScreenManager != nullptr)
    {
    m_pScreenManager->CreateAppropriateGameModeScreen();
    SetKeyPressed(true);
    }
}

GameCommands::SkipLevel::SkipLevel(dae::GameObject* owner, dae::Scene* scene, dae::LevelPrefab* level)
    :m_pScene{ scene }
    , m_pLevel{ level }
{
    m_pGameObject = owner;
}

void GameCommands::SkipLevel::Execute(float)
{
    m_pScene->Remove(m_pLevel->returnLevelObj());

    //for (auto element : m_pScene->GetGameObjects())
    //{
    //    m_pScene->Remove(element);
    //}

    //dae::SceneManager::GetInstance().

    //dae::InputManager::GetInstance().UnBindAllKeys();
}

void GameCommands::MuteMusic::Execute(float)
{
    if (GetKeyPressed()) return;

    dae::servicelocator::get_sound_system().MuteUnmute();

    SetKeyPressed(true);
}
