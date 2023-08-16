#pragma once
#include "Scene.h"
#include "TextComponent.h"

namespace dae
{

	class ScreenManager
	{
	public:
		enum GameMode
		{
			SinglePlayer,
			Coop,
			Versus
		};

		ScreenManager() = default;
		~ScreenManager() = default;
		ScreenManager(const ScreenManager& other) = delete;
		ScreenManager(ScreenManager&& other) = delete;
		ScreenManager& operator=(const ScreenManager& other) = delete;
		ScreenManager& operator=(ScreenManager&& other) = delete;

		void CreateMenuScreen();
		void CreateGameScreen();

		int GetCurrentEnum() const { return m_CurrentScreen; }
		void SetCurrentEnum(GameMode state)
		{
			m_CurrentScreen = state;
		}

		void CreateAppropriateGameModeScreen();

	private:

		GameMode m_CurrentScreen{ SinglePlayer };
		const float m_Width{ 640 };
		const float m_Height{ 480 };

		std::shared_ptr<TextComponent> m_pGameModeDisplayText;
		std::shared_ptr<GameObject> m_pGameModeDisplay;
	};

}
