#include "AIMovementComponent.h"
#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "HobbinComponent.h"

dae::AIMovementComponent::AIMovementComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_pCollision = owner->GetComponent<dae::GameCollisionComponent>();
}

void dae::AIMovementComponent::Update(float deltaTime)
{

	auto overlapPlayer = dae::GameCollisionMngr::GetInstance().CheckOverlapWithPlayers(m_pCollision);
	if(overlapPlayer != nullptr)
	{
		overlapPlayer->GetOwner()->MarkTrueForDeleting();
		dae::GameCollisionMngr::GetInstance().RemoveFirstPlayerBox(overlapPlayer);
	}

	auto hobbincompo = m_pOwner->GetComponent<dae::HobbinComponent>();

	if (hobbincompo->ReturnCharacterState() == HobbinComponent::Nobbin)
	{
		if (m_Horizontal)
		{
			bool left = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirLeft, m_pCollision);
			bool right = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirRight, m_pCollision);


			if (right)
			{
				m_CheckRight = true;
			}
			if (left)
			{
				m_CheckLeft = true;
			}


			if (!m_CheckLeft)
			{
				MoveAI(deltaTime, m_DirLeft);
			}
			else if (!m_CheckRight)
			{
				MoveAI(deltaTime, m_DirRight);
			}
		}
		else if (m_Vertical)
		{
			bool up = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirUp, m_pCollision);
			bool down = dae::GameCollisionMngr::GetInstance().AIRaycast(m_pOwner->GetRelativePosition(), m_DirDown, m_pCollision);

			if (up)
			{
				m_CheckUp = true;
			}
			if (down)
			{
				m_CheckDown = true;
			}

			if (!m_CheckUp)
			{
				MoveAI(deltaTime, m_DirUp);
			}
			else if (!m_CheckDown)
			{
				MoveAI(deltaTime, m_DirDown);
			}
		}

		if (m_CheckLeft && m_CheckRight)
		{
			m_Horizontal = false;
			m_Vertical = true;
		}
		if (m_CheckUp && m_CheckDown)
		{
			m_Horizontal = true;
			m_Vertical = false;
		}

		if (m_CheckLeft && m_CheckRight && m_CheckUp && m_CheckDown)
		{
			m_CheckLeft = false;
			m_CheckRight = false;
			m_CheckUp = false;
			m_CheckDown = false;
		}
	}
	else
	{
		auto OverlappedBox = dae::GameCollisionMngr::GetInstance().CheckForCollisionComponent(m_pCollision);

		if (OverlappedBox != nullptr)
		{
			//Dirt block delete
			if (OverlappedBox->GetOwner()->GetTag() == "Break")
			{
				dae::GameCollisionMngr::GetInstance().RemoveDirtBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
				OverlappedBox->GetOwner()->MarkTrueForDeleting();
			}
		}

		if(m_Horizontal)
		{
			const std::vector<dae::GameCollisionComponent*> pPlayers = dae::GameCollisionMngr::GetInstance().GetAllPlayers();
			//GameCollisionComponent* pClosestPlayer;

			if (pPlayers.empty()) return;

			for (auto player : pPlayers)
			{
				if (player == nullptr) return;
			}

			if (pPlayers[0]->GetOwner()->GetRelativePosition().y < m_pOwner->GetRelativePosition().y)
			{
				MoveAI(deltaTime, m_DirUp);
			}
			else if(pPlayers[0]->GetOwner()->GetRelativePosition().y > m_pOwner->GetRelativePosition().y)
			{
				MoveAI(deltaTime, m_DirDown);
			}

			const float offset{0.3f};
			if(pPlayers[0]->GetOwner()->GetRelativePosition().y < m_pOwner->GetRelativePosition().y + offset &&
				pPlayers[0]->GetOwner()->GetRelativePosition().y > m_pOwner->GetRelativePosition().y - offset)
			{
				m_Vertical = true;
				m_Horizontal = false;
			}
		}
		else if(m_Vertical)
		{
			const std::vector<dae::GameCollisionComponent*> pPlayers = dae::GameCollisionMngr::GetInstance().GetAllPlayers();
			//GameCollisionComponent* pClosestPlayer;

			if (pPlayers.empty()) return;

			for (const auto player : pPlayers)
			{
				if(player == nullptr) return;
			}

			if (pPlayers[0]->GetOwner()->GetRelativePosition().x < m_pOwner->GetRelativePosition().x)
			{
				MoveAI(deltaTime, m_DirLeft);
			}
			else if (pPlayers[0]->GetOwner()->GetRelativePosition().y > m_pOwner->GetRelativePosition().y)
			{
				MoveAI(deltaTime, m_DirRight);
			}

			const float offset{ 0.2f };
			if (pPlayers[0]->GetOwner()->GetRelativePosition().x < m_pOwner->GetRelativePosition().x - offset &&
				pPlayers[0]->GetOwner()->GetRelativePosition().y > m_pOwner->GetRelativePosition().y + offset)
			{
				m_Vertical = false;
				m_Horizontal = true;
			}
		}
	}
}

void dae::AIMovementComponent::MoveAI(float deltaTime, glm::vec2 dir) const
{
	m_pOwner->SetRelativePosition(m_pOwner->GetRelativePosition() + dir * m_Speed * deltaTime);
}
