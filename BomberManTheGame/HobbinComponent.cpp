#include "HobbinComponent.h"

#include "GameObject.h"

dae::HobbinComponent::HobbinComponent(dae::GameObject* owner)
{
	m_pOwner = owner;
	m_pTexture = owner->GetComponent<dae::TextureComponent>();
	m_Countdownvalue = m_Startvalue;
}

void dae::HobbinComponent::Update(float deltaTime)
{

	if(m_CharacterState == Nobbin)
	{
		m_pTexture->SetTexture("Sprites/Nobbin.png");
	}
	else if(m_CharacterState == Hobbin)
	{
		m_pTexture->SetTexture("Sprites/Hobbin.png");
	}

	if (m_StartTimer)
	{
		m_Countdownvalue -= 1 * deltaTime;

		if (m_Countdownvalue <= 0)
		{
			m_TimerDone = true;
			m_StartTimer = false;
			m_Countdownvalue = m_Startvalue/2;
			m_CharacterState = Hobbin;
		}
	}

	if(m_TimerDone)
	{
		m_Countdownvalue -= 1 * deltaTime;

		if (m_Countdownvalue <= 0)
		{
			m_TimerDone = false;
			m_StartTimer = true;
			m_Countdownvalue = m_Startvalue;
			m_CharacterState = Nobbin;
		}
	}
}
