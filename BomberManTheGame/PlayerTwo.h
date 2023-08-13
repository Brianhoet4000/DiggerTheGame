#pragma once
#include "GameObject.h"
#include "Scene.h"

namespace dae
{
	class PlayerTwo final
	{
	public:
		PlayerTwo(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, bool Coop);

		~PlayerTwo() = default;
		PlayerTwo(const PlayerTwo& other) = delete;
		PlayerTwo(PlayerTwo&& other) = delete;
		PlayerTwo& operator=(const PlayerTwo& other) = delete;
		PlayerTwo& operator=(PlayerTwo&& other) = delete;

	private:
		float m_Speed{ 50.f };
		glm::vec2 m_Up = { 0.f,-m_Speed };
		glm::vec2 m_Down = { 0.f,m_Speed };
		glm::vec2 m_Right = { m_Speed,0.f };
		glm::vec2 m_Left = { -m_Speed,0.f };
	};

}