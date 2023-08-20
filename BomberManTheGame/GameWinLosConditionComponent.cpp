#include "GameWinLosConditionComponent.h"

#include <iostream>

#include "EnemySpawner.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PlayerManager.h"
#include "ScreenManager.h"
#include "TextureComponent.h"

dae::GameWinLoseSingleCoopComponent::GameWinLoseSingleCoopComponent(dae::GameObject* owner, std::shared_ptr<dae::GameObject> spawner)
	:m_Finished{false}
{
	m_pOwner = owner;
	m_pSpawner = spawner;
}

void dae::GameWinLoseSingleCoopComponent::Update(float)
{
	for (const auto& player : PlayerManager::GetInstance().GetPlayers())
	{
		if (player->GetComponent<HealthComponent>()->GetAmount() <= -1)
		{
			dae::ScreenManager::GetInstance().SkipToGameOverLevel();
			return;
		}
	}
	


	if((GameCollisionMngr::GetInstance().GetAllEmerald().empty() &&
		GameCollisionMngr::GetInstance().GetAllGold().empty()) ||
		(m_pSpawner->GetComponent<dae::SpawnTimerComponent>()->RemainingNumberOfEnemies() == 0 
			&& dae::GameCollisionMngr::GetInstance().GetAllEnemies().empty()))
	{
		m_Finished = true;
	}
	
	if(m_Finished && !m_DoOnce && dae::ScreenManager::GetInstance().GetCurrentLevel() != 3)
	{
		dae::SceneManager::GetInstance().NextScene();

		if (dae::SceneManager::GetInstance().GetActiveSceneName() != "GameOver")
		{
			dae::GameCollisionMngr::GetInstance().ClearAll();
			dae::ScreenManager::GetInstance().IncrementCurrentLevel();
			dae::ScreenManager::GetInstance().CreateGameScreen(*dae::SceneManager::GetInstance().GetActiveScene());
		}

		m_DoOnce = true;
	}
}
