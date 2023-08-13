#pragma once
#include "BaseComponent.h"
#include "Scene.h"

namespace dae
{

	class SpawnTimerComponent : public dae::BaseComponent
	{
	public:
		SpawnTimerComponent(dae::Scene* scene, dae::GameObject* owner, float StartCountDownNumber);

		virtual ~SpawnTimerComponent() override = default;
		SpawnTimerComponent(const SpawnTimerComponent& other) = delete;
		SpawnTimerComponent(SpawnTimerComponent&& other) = delete;
		SpawnTimerComponent& operator=(const SpawnTimerComponent& other) = delete;
		SpawnTimerComponent& operator=(SpawnTimerComponent&& other) = delete;

		void Update(float deltaTime) override;
		void SetStartCountingDown(bool CountDownState)
		{
			m_Start = CountDownState;
		}
		bool GetBool() const { return m_Start; }

	private:
		float m_StartCountDownValue;
		float m_Counter;
		bool m_Start;
		Scene* m_pScene;
	};

}
