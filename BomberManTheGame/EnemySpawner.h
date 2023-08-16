#pragma once
#include <glm/vec2.hpp>
#include "Scene.h"

namespace dae
{

	class EnemySpawner final
	{
	public:
		EnemySpawner(dae::Scene& scene,glm::vec2 StartPos, int MaxEnemies);

		~EnemySpawner() = default;
		EnemySpawner(const EnemySpawner& other) = delete;
		EnemySpawner(EnemySpawner&& other) = delete;
		EnemySpawner& operator=(const EnemySpawner& other) = delete;
		EnemySpawner& operator=(EnemySpawner&& other) = delete;

	private:
	};

}
