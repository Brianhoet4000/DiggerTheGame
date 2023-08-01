#pragma once
#include "BaseComponent.h"

namespace dae
{

	class CountDownTimer : public dae::BaseComponent
	{
	public:
		CountDownTimer(dae::GameObject* owner, float StartCountDownNumber);

		virtual ~CountDownTimer() override = default;
		CountDownTimer(const CountDownTimer& other) = delete;
		CountDownTimer(CountDownTimer&& other) = delete;
		CountDownTimer& operator=(const CountDownTimer& other) = delete;
		CountDownTimer& operator=(CountDownTimer&& other) = delete;

		void Update(float deltaTime) override;
		void SetStartCountingDown(bool CountDownState)
		{
			m_IsDoneCountingDown = false;
			m_Start = CountDownState;
		}
		bool GetIsDoneCountingDown() const { return m_IsDoneCountingDown; }

	private:
		float m_StartCountDownValue;
		float m_Counter;
		bool m_IsDoneCountingDown;
		bool m_Start;
	};

}