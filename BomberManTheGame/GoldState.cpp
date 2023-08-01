#include "GoldState.h"
#include "CollisionBoxManager.h"
#include "GameObject.h"

dae::GoldState::GoldState(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_pTimer = m_pOwner->GetComponent<dae::CountDownTimer>();

	
}

void dae::GoldState::Update(float deltaTime)
{
	if(!m_ResetEstimatedPos)
	{
		m_EstimatedPos = m_pOwner->GetRelativePosition() + glm::vec2{0, 48};
		m_ResetEstimatedPos = true;
	}

	if (!dae::CollisionBoxManager::GetInstance().Raycast(m_pOwner->GetRelativePosition(),
		m_Direction, m_pOwner->GetComponent<CollisionBoxComponent>(), true))
	{
		if (m_pOwner->GetRelativePosition().y >= m_EstimatedPos.y - 2.f && !m_Broke)
		{
			const auto texture = m_pOwner->GetComponent<dae::TextureComponent>();
			texture->SetTexture("Sprites/Bullet.png");
			m_Broke = true;
			m_Pickup = true;
			return;
		}
		else
		{
			m_ResetEstimatedPos = false;
			return;
		}
	}

	const glm::vec2 newPos = m_pOwner->GetRelativePosition();
	m_pOwner->SetRelativePosition(newPos.x, newPos.y + m_Speed * deltaTime);
	
}
