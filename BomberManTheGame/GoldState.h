#pragma once
#include <glm/vec2.hpp>
#include "BaseComponent.h"
#include "CountDownTimer.h"

namespace dae
{

	class GoldState : public dae::BaseComponent
	{
	public:
		GoldState(dae::GameObject* owner);

		virtual ~GoldState() override = default;
		GoldState(const GoldState& other) = delete;
		GoldState(GoldState&& other) = delete;
		GoldState& operator=(const GoldState& other) = delete;
		GoldState& operator=(GoldState&& other) = delete;

		void Update(float deltaTime) override;
		bool GetPickupState() const { return m_Pickup; }

	private:
		glm::vec2 m_Direction{ 0,5 };
		dae::CountDownTimer* m_pTimer;
		const float m_Speed{ 35.f };
		glm::vec2 m_EstimatedPos;

		bool m_ResetEstimatedPos = false;
		bool m_Broke = false;
		bool m_Pickup = false;
	};

}
