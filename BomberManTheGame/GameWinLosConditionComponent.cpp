#include "GameWinLosConditionComponent.h"

#include <iostream>

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "TextureComponent.h"

dae::GameWinLosConditionComponent::GameWinLosConditionComponent(dae::GameObject* owner, dae::GameObject* level)
	:m_Finished{false}
{
	m_pOwner = owner;
	pLevel = level;
}

void dae::GameWinLosConditionComponent::Update(float)
{
	if(GameCollisionMngr::GetInstance().GetAllEmerald().empty() &&
		GameCollisionMngr::GetInstance().GetAllGold().empty())
	{
		m_Finished = true;
		pLevel->RemoveAllChilderen();
	}

	if(m_Finished)
	{
		std::cout << "You won\n";
	}
}
