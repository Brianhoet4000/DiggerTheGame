#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"
#include "LevelPrefab.h"

namespace dae
{

	class BalloonMovementComponent : public dae::BaseComponent
	{
	public:
		BalloonMovementComponent(dae::GameObject* owner, const dae::LevelPrefab& level,glm::vec2 ,const float speed);
		~BalloonMovementComponent() = default;
		BalloonMovementComponent(const BalloonMovementComponent& other) = delete;
		BalloonMovementComponent(BalloonMovementComponent&& other) = delete;
		BalloonMovementComponent& operator=(const BalloonMovementComponent& other) = delete;
		BalloonMovementComponent& operator=(BalloonMovementComponent&& other) = delete;

		virtual void Update(float) override;
		void SwitchState();

	private:
		enum MovementDir
		{
			Left,
			Up,
			Right,
			Down
		};

		glm::vec2 m_StartingPos;
		glm::vec2 m_Dir;
		MovementDir m_DirState;
		const float m_Speed;
	};

}
