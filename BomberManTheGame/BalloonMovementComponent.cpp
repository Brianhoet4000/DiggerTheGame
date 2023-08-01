#include "BalloonMovementComponent.h"
#include "BalloonMovementComponent.h"

#include "CollisionBoxManager.h"
#include "GameObject.h"

dae::BalloonMovementComponent::BalloonMovementComponent(dae::GameObject* owner,const dae::LevelPrefab& level, glm::vec2, const float speed)
	:m_Speed{speed}
{
	m_pOwner = owner;
	m_StartingPos = level.GetSpawnPosition()[1];
	m_pOwner->SetRelativePosition(m_StartingPos);
	m_DirState = MovementDir::Left;
}

void dae::BalloonMovementComponent::Update(float deltaTime)
{
	auto pos = m_pOwner->GetRelativePosition();

	SwitchState();

	m_pOwner->SetRelativePosition(pos + m_Dir * deltaTime);
}

void dae::BalloonMovementComponent::SwitchState()
{
	switch (m_DirState)
	{
	case Left:
		m_Dir = glm::vec2{ -m_Speed,0 };
		if(!dae::CollisionBoxManager::GetInstance().Raycast(m_pOwner->GetWorldPosition(), m_Dir, m_pOwner->GetComponent<CollisionBoxComponent>(), true))
		{
			m_DirState = MovementDir::Up;
		}
		break;
	case Up:
		m_Dir = glm::vec2{ 0,-m_Speed };
		if (!dae::CollisionBoxManager::GetInstance().Raycast(m_pOwner->GetWorldPosition(), m_Dir, m_pOwner->GetComponent<CollisionBoxComponent>(), true))
		{
			m_DirState = MovementDir::Right;
		}
		break;
	case Right:
		m_Dir = glm::vec2{ m_Speed ,0 };
		if (!dae::CollisionBoxManager::GetInstance().Raycast(m_pOwner->GetWorldPosition(), m_Dir, m_pOwner->GetComponent<CollisionBoxComponent>(), true))
		{
			m_DirState = MovementDir::Down;
		}
		break;
	case Down:
		m_Dir = glm::vec2{ 0 ,m_Speed };
		if (!dae::CollisionBoxManager::GetInstance().Raycast(m_pOwner->GetWorldPosition(), m_Dir, m_pOwner->GetComponent<CollisionBoxComponent>(), true))
		{
			m_DirState = MovementDir::Left;
		}
		break;
	}
}
