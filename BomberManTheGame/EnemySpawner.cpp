#include "EnemySpawner.h"
#include <memory>
#include "SpawnTimerComponent.h"
#include "EnemyPrefab.h"
#include "GameObject.h"
#include "TextureComponent.h"

dae::EnemySpawner::EnemySpawner(dae::Scene& scene, glm::vec2 StartPos, int MaxEnemies)
{
	auto pSpawnObj = std::make_shared<dae::GameObject>();
	pSpawnObj->SetRelativePosition(StartPos);

	auto pTexture = std::make_shared<dae::TextureComponent>(pSpawnObj.get());
	pTexture->SetTexture("Sprites/Cherry.png");
	pTexture->SetMustRender(false);
	pSpawnObj->AddComponent(pTexture);

	//Timer
	auto pTimer = std::make_shared<dae::SpawnTimerComponent>(&scene, pSpawnObj.get(), 7.f, MaxEnemies);
	pSpawnObj->AddComponent(pTimer);

	scene.Add(pSpawnObj);
}
