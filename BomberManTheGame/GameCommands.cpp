#include "GameCommands.h"

#include "Bullet.h"
#include "CollisionBoxManager.h"
#include "GameCollisionMngr.h"
#include "GoldStateComponent.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "ShootingDirComponent.h"

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
   
    //glm::vec2 upMiddel = { m_pGameObject->GetRelativePosition().x / 2 , m_pGameObject->GetRelativePosition().y };
    //glm::vec2 downMiddel = { m_pGameObject->GetRelativePosition().x , m_pGameObject->GetRelativePosition().y + 24 };
    //glm::vec2 Leftmiddel = { m_pGameObject->GetRelativePosition().x , m_pGameObject->GetRelativePosition().y + 12 };
    //glm::vec2 Rightmiddel = { m_pGameObject->GetRelativePosition().x + 24 , m_pGameObject->GetRelativePosition().y + 12 };

    if (m_Digger) //Single/Coop -> Digger
    {
        //ShootingDir
        {
            auto shootingstate = m_pGameObject->GetComponent<dae::ShootingDirComponent>();

            if (m_Dir.x > 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Right);
            }
            if (m_Dir.x < 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Left);
            }
            if (m_Dir.y < 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Up);
            }
            if (m_Dir.y > 0)
            {
                shootingstate->SetFaceState(dae::ShootingDirComponent::Down);
            }
        }

        dae::GameCollisionMngr::GetInstance().PlayerLogicBox(m_pGameObject->GetComponent<dae::GameCollisionComponent>(), m_Dir);

        if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, false))
            return;
    }
    else //Verus -> Nobbin
    {
        dae::GameCollisionMngr::GetInstance().NobbinLogicBox(m_pGameObject->GetComponent<dae::GameCollisionComponent>(), m_Dir);

    	if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pGameObject->GetRelativePosition(), m_Dir, m_pCollision, true))
            return;
       
    }

    pos.x += m_Dir.x * deltaTime;
    pos.y += m_Dir.y * deltaTime;
    
    m_pGameObject->SetRelativePosition(pos);
}

GameCommands::ShootingBullet::ShootingBullet(dae::GameObject* owner,dae::Scene* scene)
{
    m_pGameObject = owner;
    m_Scene = scene;
    m_pBulletTimer = owner->GetComponent<dae::BulletTimerComponent>();
}

void GameCommands::ShootingBullet::Execute(float)
{
    if(GetKeyPressed()) return;

    if (m_pBulletTimer->ReturnHasShot()) return;

    auto shootingState = m_pGameObject->GetComponent<dae::ShootingDirComponent>();

    if(shootingState->returnFaceState() == dae::ShootingDirComponent::Right)
    {
        m_Dir = { 1,0 };
    }
    if (shootingState->returnFaceState() == dae::ShootingDirComponent::Left)
    {
        m_Dir = { -1,0 };
    }
    if (shootingState->returnFaceState() == dae::ShootingDirComponent::Up)
    {
        m_Dir = { 0,-1 };
    }
    if (shootingState->returnFaceState() == dae::ShootingDirComponent::Down)
    {
        m_Dir = { 0,1 };
    }

    auto bullet = std::make_shared<dae::Bullet>(m_pGameObject->GetRelativePosition(), m_Dir);
    m_pBulletTimer->SetHasShot(true);
    m_Scene->Add(bullet->ReturnBullet());

    SetKeyPressed(true);
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

    auto text = m_pTextMode->GetComponent<dae::TextComponent>();

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
}

void GameCommands::MuteMusic::Execute(float)
{
    if (GetKeyPressed()) return;

    dae::servicelocator::get_sound_system().MuteUnmute();

    SetKeyPressed(true);
}
