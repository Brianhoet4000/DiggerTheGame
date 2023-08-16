#pragma once
#include "BaseComponent.h"

namespace dae
{

	class GameWinLosConditionComponent : public dae::BaseComponent
	{
	public:

		GameWinLosConditionComponent(dae::GameObject* owner, dae::GameObject* level);
		virtual ~GameWinLosConditionComponent() = default;
		GameWinLosConditionComponent(const GameWinLosConditionComponent& other) = delete;
		GameWinLosConditionComponent(GameWinLosConditionComponent&& other) = delete;
		GameWinLosConditionComponent& operator=(const GameWinLosConditionComponent& other) = delete;
		GameWinLosConditionComponent& operator=(GameWinLosConditionComponent&& other) = delete;

		void Update(float) override;

	private:
		bool m_Finished;
		GameObject* pLevel;
	};

}