#pragma once
#include "GameObject.h"
#include "LevelPrefab.h"
#include "Scene.h"

namespace dae
{
	class PlayerOne final
	{
	public:
		PlayerOne(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, LevelPrefab* level, bool ControllerEnabled);

		~PlayerOne() = default;
		PlayerOne(const PlayerOne& other) = delete;
		PlayerOne(PlayerOne&& other) = delete;
		PlayerOne& operator=(const PlayerOne& other) = delete;
		PlayerOne& operator=(PlayerOne&& other) = delete;

	private:
		const float speed{ 50.f };
		glm::vec2 up = { 0.f,-speed };
		glm::vec2 down = { 0.f,speed };
		glm::vec2 right = { speed,0.f };
		glm::vec2 left = { -speed,0.f };
		
	};
}