#pragma once
#include <vector>

#include "CollisionBoxComponent.h"
#include "Singleton.h"
#include <SDL_rect.h>

namespace dae
{
	class CollisionBoxManager : public Singleton<CollisionBoxManager>
	{
	public:
		CollisionBoxManager() = default;
		virtual ~CollisionBoxManager() = default;
		CollisionBoxManager(const CollisionBoxManager& other) = delete;
		CollisionBoxManager(CollisionBoxManager&& other) = delete;
		CollisionBoxManager& operator=(const CollisionBoxManager& other) = delete;
		CollisionBoxManager& operator=(CollisionBoxManager&& other) = delete;

		void AddCollisionBox(dae::GameObject* owner, CollisionBoxComponent* box);
		void RemoveCollisionBox(CollisionBoxComponent* box);
		void RemoveDirtBox(CollisionBoxComponent* box);
		void RemoveEmeraldBox(CollisionBoxComponent* box);

		std::vector<CollisionBoxComponent*> GetAllWallColliders();
		std::vector<CollisionBoxComponent*> GetAllDirtColliders();
		std::vector<CollisionBoxComponent*> GetAllEmeraldColliders();

		bool CheckForCollision(CollisionBoxComponent* box);
		CollisionBoxComponent* CheckForCollisionComponent(CollisionBoxComponent* box);
		bool CheckForOverlapDirt(dae::CollisionBoxComponent* box);

		bool Raycast(glm::vec2 startpos, glm::vec2 direction, dae::CollisionBoxComponent* collisionbox, bool checkDirt);

	private:
		std::vector<CollisionBoxComponent*> m_pCollisonBoxes;
		std::vector<CollisionBoxComponent*> m_pWallBoxes;
		std::vector<CollisionBoxComponent*> m_pDirtBoxes;
		std::vector<CollisionBoxComponent*> m_pEmeraldBoxes;
		std::vector<dae::GameObject*> m_pOwners;
		bool m_GetAllCollisions = false;
	};

}