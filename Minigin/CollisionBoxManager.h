#pragma once
#include <vector>

#include "CollisionBoxComponent.h"
#include "Singleton.h"
#include <glm/vec2.hpp>

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

		bool CheckForCollision(const CollisionBoxComponent* box) const;
		CollisionBoxComponent* CheckForCollisionComponent(const CollisionBoxComponent* box) const;

		bool Raycast(glm::vec2 startpos, glm::vec2 direction, dae::CollisionBoxComponent* collisionbox) const;

	private:
		std::vector<CollisionBoxComponent*> m_pCollisonBoxes;
		std::vector<dae::GameObject*> m_pOwners;
	};

}
