#include "EnemyPrefab.h"

#include "AIMovementComponent.h"
#include "GameCollisionComponent.h"
#include "HobbinComponent.h"
#include "TextureComponent.h"

dae::EnemyPrefab::EnemyPrefab(dae::Scene& scene, glm::vec2 StartPos)
{
	auto pEnemyGameObject = std::make_shared<dae::GameObject>("Enemy");
	pEnemyGameObject->SetRelativePosition(StartPos);

	//Texture
	auto pTexture = std::make_shared<dae::TextureComponent>(pEnemyGameObject.get());
	pTexture->SetTexture("Sprites/Nobbin.png");
	pEnemyGameObject->AddComponent(pTexture);

	//Collision
	auto pCollider = std::make_shared<dae::GameCollisionComponent>(pEnemyGameObject.get());
	pEnemyGameObject->AddComponent(pCollider);
	//Collider->SetCollisionRectOffset(5.f);
	pCollider->SetRenderCollisionBox(true);

	//Hobbin
	auto hobbinComponent = std::make_shared<dae::HobbinComponent>(pEnemyGameObject.get());
	pEnemyGameObject->AddComponent(hobbinComponent);

	//AIMovement
	auto AIMovement = std::make_shared<dae::AIMovementComponent>(pEnemyGameObject.get());
	pEnemyGameObject->AddComponent(AIMovement);

	scene.Add(pEnemyGameObject);
}
