#include "GameWinLosConditionComponent.h"

#include <iostream>

#include "EnemySpawner.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "ScreenManager.h"
#include "TextureComponent.h"

dae::GameWinLosConditionComponent::GameWinLosConditionComponent(dae::GameObject* owner, std::shared_ptr<dae::GameObject> Spawner)
	:m_Finished{false}
{
	m_pOwner = owner;
	m_pSpawner = Spawner;
}

void dae::GameWinLosConditionComponent::Update(float)
{
	if((GameCollisionMngr::GetInstance().GetAllEmerald().empty() &&
		GameCollisionMngr::GetInstance().GetAllGold().empty()) ||
		(m_pSpawner->GetComponent<dae::SpawnTimerComponent>()->RemainingNumberOfEnemies() == 0 
			&& dae::GameCollisionMngr::GetInstance().GetAllEnemies().empty()))
	{
		m_Finished = true;
	}

	if (m_Finished && !m_DoOnce && dae::ScreenManager::GetInstance().GetCurrentLevel() == 3)
	{
		//dae::ScreenManager::GetInstance().CreateGameOverScreen();
		m_DoOnce = true;
	}

	
	if(m_Finished && !m_DoOnce && dae::ScreenManager::GetInstance().GetCurrentLevel() != 3)
	{
		dae::ScreenManager::GetInstance().IncrementCurrentLevel();
		//dae::ScreenManager::GetInstance().CreateGameScreen();
		m_DoOnce = true;
	}
}
