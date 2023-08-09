#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "GameCollisionComponent.h"


namespace dae
{

	class AIMovementComponent : public dae::BaseComponent
	{
	public:

		enum MovementDir
		{
			Left,
			Right,
			Up,
			Down
		};


		AIMovementComponent(dae::GameObject* owner);
		virtual ~AIMovementComponent() override = default;
		AIMovementComponent(const AIMovementComponent& other) = delete;
		AIMovementComponent(AIMovementComponent&& other) = delete;
		AIMovementComponent& operator=(const AIMovementComponent& other) = delete;
		AIMovementComponent& operator=(AIMovementComponent&& other) = delete;

		void Update(float deltaTime) override;

	private:
		float m_Speed{70.f};
		GameCollisionComponent* m_pCollision;
		glm::vec2 m_DirLeft{-1,0};
		glm::vec2 m_DirRight{1, 0};
		glm::vec2 m_DirUp{0, -1};
		glm::vec2 m_DirDown{0, 1};

		MovementDir m_MovementDir{ Left };
		bool m_Horizontal = true;
		bool m_Vertical = false;

		bool m_CheckLeft = false;
		bool m_CheckRight = false;
		bool m_CheckUp = false;
		bool m_CheckDown = false;
	};

}