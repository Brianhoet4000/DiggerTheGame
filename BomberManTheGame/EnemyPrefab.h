#pragma once
#include "GameObject.h"
#include "LevelPrefab.h"
#include "Scene.h"

namespace dae
{

	class EnemyPrefab final
	{
	public:
		EnemyPrefab(dae::Scene& scene, glm::vec2 StartPos);

		~EnemyPrefab() = default;
		EnemyPrefab(const EnemyPrefab& other) = delete;
		EnemyPrefab(EnemyPrefab&& other) = delete;
		EnemyPrefab& operator=(const EnemyPrefab& other) = delete;
		EnemyPrefab& operator=(EnemyPrefab&& other) = delete;

	private:

	};

}