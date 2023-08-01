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
		const float speed{ 50.f };
		glm::vec2 up = { 0.f,-speed };
		glm::vec2 down = { 0.f,speed };
		glm::vec2 right = { speed,0.f };
		glm::vec2 left = { -speed,0.f };
	};

}