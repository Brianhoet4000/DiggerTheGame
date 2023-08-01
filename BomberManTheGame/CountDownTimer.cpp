#include "CountDownTimer.h"

#include <iostream>

#include "GameObject.h"

dae::CountDownTimer::CountDownTimer(dae::GameObject* owner,float StartCountDownNumber)
	:m_StartCountDownValue(StartCountDownNumber)
{
	m_IsDoneCountingDown = false;
	m_Start = false;
	m_Counter = m_StartCountDownValue;
	m_pOwner = owner;
}

void dae::CountDownTimer::Update(float deltaTime)
{
	if(m_Start && !m_IsDoneCountingDown)
	{
		m_Counter -= 1.f * deltaTime;

		if(m_Counter <= 0.f)
		{
			m_IsDoneCountingDown = true;
			m_Counter = m_StartCountDownValue;
		}
	}
}