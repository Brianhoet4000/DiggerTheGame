#pragma once
#include "PlayerOne.h"
#include "Scene.h"
#include "TextComponent.h"

namespace dae
{

	class ScreenManager final : public Singleton<ScreenManager>
	{
	public:
		enum GameMode
		{
			SinglePlayer,
			Coop,
			Versus
		};
		
		virtual ~ScreenManager() = default;
		ScreenManager(const ScreenManager& other) = delete;
		ScreenManager(ScreenManager&& other) = delete;
		ScreenManager& operator=(const ScreenManager& other) = delete;
		ScreenManager& operator=(ScreenManager&& other) = delete;

		void CreateMenuScreen(dae::Scene& scene);
		void CreateGameScreen(dae::Scene& scene);

		void CreateGameOverScreen(dae::Scene& scene);

		int GetCurrentEnum() const { return m_CurrentGameMode; }
		void SetCurrentEnum(GameMode state)
		{
			m_CurrentGameMode = state;
		}

		int GetCurrentLevel() { return m_CurrentLevel; }
		void IncrementCurrentLevel() { ++m_CurrentLevel; }

		void CreateLevelZero(dae::Scene& scene);
		void CreateLevelOne(dae::Scene& scene);
		void CreateLevelTwo(dae::Scene& scene);

	private:
		friend class Singleton<ScreenManager>;
		ScreenManager() = default;
		GameMode m_CurrentGameMode{ SinglePlayer };
		const float m_Width{ 640 };
		const float m_Height{ 480 };

		std::shared_ptr<TextComponent> m_pGameModeDisplayText;
		std::shared_ptr<GameObject> m_pGameModeDisplay;
		int m_CurrentLevel{ 0 };
		bool m_AddedPlayers = false;
	};

}
