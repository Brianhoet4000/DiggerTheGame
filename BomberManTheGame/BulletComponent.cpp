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
	const auto pColliderBullet = m_pOwner->GetComponent<dae::GameCollisionComponent>();

	if(dae::GameCollisionMngr::GetInstance().CheckForOverlapDirt(pColliderBullet) ||
		dae::GameCollisionMngr::GetInstance().CheckForOverlapWall(pColliderBullet))
	{
		m_pOwner->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);
	}

	//If in versus mode
	const auto enemy = dae::GameCollisionMngr::GetInstance().CheckOverlapWithSecondPlayerVersus(pColliderBullet);
	if(enemy != nullptr)
	{
		enemy->GetOwner()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(enemy->GetOwner()->GetComponent<dae::GameCollisionComponent>());

		m_pOwner->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveBulletBox(pColliderBullet);
	}

	const float Speed{75.f};
	const auto newPos = m_pOwner->GetRelativePosition() + m_vel * Speed * deltaTime;
	m_pOwner->SetRelativePosition(newPos);


}
