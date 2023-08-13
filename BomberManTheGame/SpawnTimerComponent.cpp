#include "SpawnTimerComponent.h"
#include <iostream>

#include "EnemyPrefab.h"
#include "GameObject.h"

dae::SpawnTimerComponent::SpawnTimerComponent(dae::Scene* scene, dae::GameObject* owner,float StartCountDownNumber)
	:m_StartCountDownValue(StartCountDownNumber)
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

		m_Start = true;
	}


	if (m_Start)
	{
		m_Counter -= 1 * deltaTime;

		if (m_Counter <= 0)
		{
			m_Start = false;
			m_Counter = m_StartCountDownValue;
		}
	}
}