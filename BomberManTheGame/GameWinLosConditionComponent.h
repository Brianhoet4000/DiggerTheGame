#pragma once
#include "BaseComponent.h"
#include "EnemySpawner.h"

namespace dae
{

	class GameWinLosConditionComponent : public dae::BaseComponent
	{
	public:

		GameWinLosConditionComponent(dae::GameObject* owner, std::shared_ptr<dae::GameObject> Spawner);
		virtual ~GameWinLosConditionComponent() = default;
		GameWinLosConditionComponent(const GameWinLosConditionComponent& other) = delete;
		GameWinLosConditionComponent(GameWinLosConditionComponent&& other) = delete;
		GameWinLosConditionComponent& operator=(const GameWinLosConditionComponent& other) = delete;
		GameWinLosConditionComponent& operator=(GameWinLosConditionComponent&& other) = delete;

		void Update(float) override;

	private:
		bool m_Finished;
		std::shared_ptr<dae::GameObject> m_pSpawner;
		bool m_DoOnce = false;
	};

}
