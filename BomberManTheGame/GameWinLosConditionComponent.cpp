#include "GameWinLosConditionComponent.h"

#include "GameCollisionMngr.h"

dae::GameWinLosConditionComponent::GameWinLosConditionComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
}

void dae::GameWinLosConditionComponent::Update(float)
{
	if(GameCollisionMngr::GetInstance().GetAllEmerald().empty() &&
		GameCollisionMngr::GetInstance().GetAllGold().empty())
	{
		
	}
}
