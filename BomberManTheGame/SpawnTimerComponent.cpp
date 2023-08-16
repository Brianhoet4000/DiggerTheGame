#include "SpawnTimerComponent.h"
#include <iostream>

#include "EnemyPrefab.h"
#include "GameObject.h"

dae::SpawnTimerComponent::SpawnTimerComponent(dae::Scene* scene, dae::GameObject* owner,float StartCountDownNumber, int MaxNumberOfEnemies)
	:m_StartCountDownValue{StartCountDownNumber}
	,m_MaxNumberOfEnemies{MaxNumberOfEnemies}
	,m_EnemyNumber{0}
{
	m_Start = false;
	m_Counter = m_StartCountDownValue;
	m_pOwner = owner;
	m_pScene = scene;
}

void dae::SpawnTimerComponent::Update(float deltaTime)
{
	if (!m_Start)
	{
		auto enemy = std::make_shared<dae::EnemyPrefab>(*m_pScene, m_pOwner->GetRelativePosition());
		m_pScene->Add(enemy->returnGameObject());
		++m_EnemyNumber;
		m_Start = true;
	}


	if (m_Start)
	{
		m_Counter -= 1 * deltaTime;

		if (m_Counter <= 0)
		{
			if (m_EnemyNumber != m_MaxNumberOfEnemies)
			{
				m_Start = false;
				m_Counter = m_StartCountDownValue;
			}
		}
	}
}