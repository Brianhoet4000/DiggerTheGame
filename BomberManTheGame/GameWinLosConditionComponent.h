#pragma once
#include "BaseComponent.h"
#include "EnemySpawner.h"

namespace dae
{

	class GameWinLoseSingleCoopComponent : public dae::BaseComponent
	{
	public:

		GameWinLoseSingleCoopComponent(dae::GameObject* owner, std::shared_ptr<dae::GameObject> spawner);
		virtual ~GameWinLoseSingleCoopComponent() = default;
		GameWinLoseSingleCoopComponent(const GameWinLoseSingleCoopComponent& other) = delete;
		GameWinLoseSingleCoopComponent(GameWinLoseSingleCoopComponent&& other) = delete;
		GameWinLoseSingleCoopComponent& operator=(const GameWinLoseSingleCoopComponent& other) = delete;
		GameWinLoseSingleCoopComponent& operator=(GameWinLoseSingleCoopComponent&& other) = delete;

		void Update(float) override;

	private:
		bool m_Finished;
		std::shared_ptr<dae::GameObject> m_pSpawner;
		bool m_DoOnce = false;
	};

}
