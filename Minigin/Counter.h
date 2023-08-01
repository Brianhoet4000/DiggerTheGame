#pragma once
#include "BaseComponent.h"
#include <string>
#include <iostream>

namespace dae
{

	class CounterComponent : public BaseComponent
	{
	public:
		CounterComponent(GameObject* owner, int startAmount);

		void ChangeAmount(int difference);
		void SetAmount(int newHealth);
		int GetAmount() const;

	private:
		int m_Counter{};

	};

	class HealthComponent final : public CounterComponent
	{
	public:
		HealthComponent(GameObject* owner, int startAmount) :
			CounterComponent(owner, startAmount) {};
	};

	class PointsComponent final : public CounterComponent
	{
	public:
		PointsComponent(GameObject* owner, int startAmount) :
			CounterComponent(owner, startAmount) {};
	};
}
