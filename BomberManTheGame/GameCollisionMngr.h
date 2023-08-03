#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "GameCollisionComponent.h"
#include "Singleton.h"

namespace dae
{
	class GameObject;

	class GameCollisionMngr : public dae::Singleton<GameCollisionMngr>
	{
	public:
		GameCollisionMngr() = default;
		virtual ~GameCollisionMngr() = default;
		GameCollisionMngr(const GameCollisionMngr& other) = delete;
		GameCollisionMngr(GameCollisionMngr&& other) = delete;
		GameCollisionMngr& operator=(const GameCollisionMngr& other) = delete;
		GameCollisionMngr& operator=(GameCollisionMngr&& other) = delete;

		void AddCollisionBox(dae::GameObject* owner, GameCollisionComponent* box);
		void RemoveCollisionBox(GameCollisionComponent* box);
		void RemoveDirtBox(GameCollisionComponent* box);
		void RemoveEmeraldBox(GameCollisionComponent* box);
		void RemoveGoldBox(GameCollisionComponent* box);

		std::vector<GameCollisionComponent*> GetAllWallColliders();
		std::vector<GameCollisionComponent*> GetAllDirtColliders();
		std::vector<GameCollisionComponent*> GetAllEmeraldColliders();
		std::vector<GameCollisionComponent*> GetAllGoldColliders();

		bool CheckForCollision(const GameCollisionComponent* box) const;
		GameCollisionComponent* CheckForCollisionComponent(const GameCollisionComponent* box) const;
		GameCollisionComponent* CheckForGoldCollisionComponent(const GameCollisionComponent* box) const;
		GameCollisionComponent* CheckForDirtCollisionComponent(const GameCollisionComponent* box) const;
		bool CheckForOverlapDirt(const dae::GameCollisionComponent* box) const;
		bool CheckForOverlapBrokenGold(const dae::GameCollisionComponent* box) const;

		void PlayerLogicBox(const dae::GameCollisionComponent* ownerBox, glm::vec2 dir);
		void NobbinLogicBox(const dae::GameCollisionComponent* ownerBox, glm::vec2 dir);

		bool Raycast(glm::vec2 startpos, glm::vec2 direction,const dae::GameCollisionComponent* collisionbox, bool checkDirt) const;

	private:
		std::vector<GameCollisionComponent*> m_pCollisonBoxes;
		std::vector<GameCollisionComponent*> m_pWallBoxes;
		std::vector<GameCollisionComponent*> m_pDirtBoxes;
		std::vector<GameCollisionComponent*> m_pEmeraldBoxes;
		std::vector<GameCollisionComponent*> m_pGoldBoxes;
		const float m_Dim = 24.f;
	};

}