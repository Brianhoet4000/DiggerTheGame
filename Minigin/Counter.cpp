#pragma once
#include "Counter.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"



using namespace dae;

CounterComponent::CounterComponent(GameObject* owner, int startAmount) :
	m_Counter{ startAmount }
{
	m_pOwner = owner;
}

void CounterComponent::ChangeAmount(int difference)
{
	m_Counter += difference;

	if (m_Counter < 0)
	{
		m_Counter = 0;
		m_pOwner->MarkTrueForDeleting();
	}
}

void CounterComponent::SetAmount(int newHealth)
{
	if (newHealth < 0)
		return;

	m_Counter = newHealth;

	if (m_Counter == 0)
		m_pOwner->MarkTrueForDeleting();
}

int CounterComponent::GetAmount() const
{
	return m_Counter;
}

