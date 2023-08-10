#include "AIMovementComponent.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"

dae::AIMovementComponent::AIMovementComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_pCollision = owner->GetComponent<dae::GameCollisionComponent>();
}

void dae::AIMovementComponent::Update(float)
{
	//bool left = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirLeft, m_pCollision);
	//bool right = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirRight, m_pCollision);
	//bool up = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirUp, m_pCollision);
	//bool down = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirDown, m_pCollision);

	//std::cout << "L: " << left << "\n";
	//std::cout << "R: " << right << "\n";
	//std::cout << "U: " << up << "\n";
	//std::cout << "D: " << down << "\n";


}
