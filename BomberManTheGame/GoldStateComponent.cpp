#include "GoldStateComponent.h"
#include "CollisionBoxManager.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "TextureComponent.h"

dae::GoldStateComponent::GoldStateComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_pTimer = m_pOwner->GetComponent<dae::CountDownTimer>();
	m_EstimatedPos = glm::vec2{ 0,0 };
	
}

void dae::GoldStateComponent::Update(float deltaTime)
{
	if(!m_ResetEstimatedPos)
	{
		m_EstimatedPos = m_pOwner->GetRelativePosition() + glm::vec2{0, 48};
		m_ResetEstimatedPos = true;
	}

	if (!dae::GameCollisionMngr::GetInstance().Raycast(m_pOwner->GetRelativePosition(),
		m_Direction, m_pOwner->GetComponent<GameCollisionComponent>(), true))
	{
		if (m_pOwner->GetRelativePosition().y >= m_EstimatedPos.y - 2.f && !m_Broke)
		{
			//Here Coins
			const auto texture = m_pOwner->GetComponent<dae::TextureComponent>();
			texture->SetTexture("Sprites/Gold.png");
			m_Broke = true;
			m_MoneyState = Coins;
			dae::servicelocator::get_sound_system().playSound(2, 20);
			return;
		}
		else
		{
			//Still MoneyBag
			m_ResetEstimatedPos = false;
			m_MoneyState = Full;
			return;
		}
	}

	//Falling
	const glm::vec2 newPos = m_pOwner->GetRelativePosition();
	m_MoneyState = Falling;
	m_pOwner->SetRelativePosition(newPos.x, newPos.y + m_Speed * deltaTime);
	
}
