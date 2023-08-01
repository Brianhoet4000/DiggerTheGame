#pragma once
#include "Event.h"
#include <string>

namespace dae
{
	class GameObject;


	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void Notify(dae::Event event, dae::GameObject* gameObject) = 0;
	};

	class UI final : public Observer
	{
	public:
		virtual void Notify(dae::Event event, dae::GameObject* gameObject);


	private:
		void UpdateUI(dae::GameObject* owner, const std::string& type);
	};

}