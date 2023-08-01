#pragma once
#include "GameObject.h"


namespace dae
{

	class Emerald
	{
	public:
		Emerald(dae::GameObject* owner, glm::vec2 pos);
		std::shared_ptr<dae::GameObject> ReturnEmerald() { return m_pEmerald; }

		~Emerald() = default;
		Emerald(const Emerald& other) = delete;
		Emerald(Emerald&& other) = delete;
		Emerald& operator=(const Emerald& other) = delete;
		Emerald& operator=(Emerald&& other) = delete;

	private:
		std::shared_ptr<dae::GameObject> m_pEmerald;

	};

}
