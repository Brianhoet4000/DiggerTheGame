#include "BulletComponent.h"

#include <memory>
#include <glm/vec2.hpp>

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "TextureComponent.h"


dae::BulletComponent::BulletComponent(dae::GameObject* owner, glm::vec2 vel)
	:m_vel{vel}
{
	m_pOwner = owner;
}

void dae::BulletComponent::Update(float deltaTime)
{

	if(dae::GameCollisionMngr::GetInstance().CheckForOverlapDirt(m_pOwner->GetComponent<dae::GameCollisionComponent>()) ||
		dae::GameCollisionMngr::GetInstance().CheckForOverlapWall(m_pOwner->GetComponent<dae::GameCollisionComponent>()))
	{
		m_pOwner->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(m_pOwner->GetComponent<dae::GameCollisionComponent>());
	}

	auto enemy = dae::GameCollisionMngr::GetInstance().CheckOverlapWithSecondPlayerVersus(m_pOwner->GetComponent<dae::GameCollisionComponent>());
	if(enemy != nullptr)
	{
		enemy->GetOwner()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(enemy->GetOwner()->GetComponent<dae::GameCollisionComponent>());

		m_pOwner->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(m_pOwner->GetComponent<dae::GameCollisionComponent>());
	}

	const float Speed{75.f};
	const auto newPos = m_pOwner->GetRelativePosition() + m_vel * Speed * deltaTime;
	m_pOwner->SetRelativePosition(newPos);


}
