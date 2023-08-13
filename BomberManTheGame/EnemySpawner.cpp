#include "EnemySpawner.h"

#include <memory>

#include "SpawnTimerComponent.h"
#include "EnemyPrefab.h"
#include "GameObject.h"

dae::EnemySpawner::EnemySpawner(dae::Scene& scene, glm::vec2 StartPos)
{
	auto pSpawnObj = std::make_shared<dae::GameObject>();
	pSpawnObj->SetRelativePosition(StartPos);

	//Timer
	auto pTimer = std::make_shared<dae::SpawnTimerComponent>(&scene, pSpawnObj.get(), 7.f);
	pSpawnObj->AddComponent(pTimer);

	scene.Add(pSpawnObj);
}
