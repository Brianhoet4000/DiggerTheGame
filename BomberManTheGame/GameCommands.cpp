#include "GameCommands.h"

#include "CollisionBoxManager.h"
#include "GameCollisionMngr.h"
#include "GoldState.h"
#include "InputManager.h"
#include "ServiceLocator.h"

GameCommands::DiggerMovement::DiggerMovement(dae::GameObject* owner, const glm::vec2& dir, bool digger)
{
	m_pGameObject = owner;
	m_Dir = dir;
    m_pCollision = m_pGameObject->GetComponent<dae::GameCollisionComponent>();
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
        auto OverlappedBox = dae::GameCollisionMngr::GetInstance().CheckForCollisionComponent(m_pGameObject->GetComponent<dae::GameCollisionComponent>());

        if (OverlappedBox != nullptr)
        {
            //Dirt block delete
            if (OverlappedBox->GetOwner()->GetTag() == "Break")
            {
                dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                dae::GameCollisionMngr::GetInstance().RemoveDirtBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
            }

            //Overlap with emerald pick up
            if (OverlappedBox->GetOwner()->GetTag() == "Emerald")
            {
                dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                dae::GameCollisionMngr::GetInstance().RemoveEmeraldBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
            }

            //Gold Related
            {
                //Push Gold Left
                if (OverlappedBox->GetOwner()->GetTag() == "Gold" &&
                    !OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState() && m_Dir.x > 0)
                {
                    glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x + 24, OverlappedBox->GetOwner()->GetRelativePosition().y };
                    OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                }
                //Push Gold Right
                else if (OverlappedBox->GetOwner()->GetTag() == "Gold" &&
                    !OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState() && m_Dir.x < 0)
                {
                    glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x - 24, OverlappedBox->GetOwner()->GetRelativePosition().y };
                    OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                }

                //If Gold Broken and overlap pick up
                if (OverlappedBox->GetOwner()->GetTag() == "Gold" && OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState())
                {
                    dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    dae::GameCollisionMngr::GetInstance().RemoveGoldBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    OverlappedBox->GetOwner()->MarkTrueForDeleting();
                }
            }
        }

        if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, false))
            return;
    }
    else //Verus -> Nobbin
    {
        auto OverlappedBox = dae::GameCollisionMngr::GetInstance().CheckForGoldCollisionComponent(m_pGameObject->GetComponent<dae::GameCollisionComponent>());
        auto OtherOverLappedBox = dae::GameCollisionMngr::GetInstance().CheckForDirtCollisionComponent(m_pGameObject->GetComponent<dae::GameCollisionComponent>());
        //Gold Nobbin
        if (OverlappedBox != nullptr)
        {
            {
                if (OtherOverLappedBox != nullptr)
                {
                    //Push Gold Left
                    if (OverlappedBox->GetOwner()->GetTag() == "Gold" && OtherOverLappedBox->GetOwner()->GetTag() == "Break" &&
                        !OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState() && m_Dir.x > 0)
                    {
                        OtherOverLappedBox->GetOwner()->MarkTrueForDeleting();
                        dae::GameCollisionMngr::GetInstance().RemoveDirtBox(OtherOverLappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());


                        glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x + 24, OverlappedBox->GetOwner()->GetRelativePosition().y };
                        OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                    }
                    //Push Gold Right
                    else if (OverlappedBox->GetOwner()->GetTag() == "Gold" && OtherOverLappedBox->GetOwner()->GetTag() == "Break" &&
                        !OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState() && m_Dir.x < 0)
                    {
                        OtherOverLappedBox->GetOwner()->MarkTrueForDeleting();
                        dae::GameCollisionMngr::GetInstance().RemoveDirtBox(OtherOverLappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());

                        glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x - 24, OverlappedBox->GetOwner()->GetRelativePosition().y };
                        OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                    }
                }

                //If Gold Broken and overlap pick up
                if (OverlappedBox->GetOwner()->GetTag() == "Gold" && OverlappedBox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState())
                {
                    dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    dae::GameCollisionMngr::GetInstance().RemoveGoldBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    OverlappedBox->GetOwner()->MarkTrueForDeleting();
                }
            }
        }

    	if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, true))
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
