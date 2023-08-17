#include "ScreenManager.h"
#include <SDL_scancode.h>
#include <glm/vec2.hpp>
#include "EnemyPrefab.h"
#include "EnemySpawner.h"
#include "GameCommands.h"
#include "FPSCounterComponent.h"
#include "GameWinLosConditionComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"

namespace dae
{

	void dae::ScreenManager::CreateMenuScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Main");

		auto GameObjBackGround = std::make_shared<dae::GameObject>();
		auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
		go->SetTexture("background.png");
		GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
		GameObjBackGround->AddComponent(go);
		scene.Add(GameObjBackGround);

		//Controls
		{
			auto pKeyboardControls = std::make_shared<dae::GameObject>();
			auto pKeyboard = std::make_shared<dae::TextureComponent>(pKeyboardControls.get());
			pKeyboard->SetTexture("Controls/WASDSpace.png");
			pKeyboardControls->SetRelativePosition(m_Width / 6, 300);
			pKeyboardControls->AddComponent(pKeyboard);
			scene.Add(pKeyboardControls);

			auto pControllerControls = std::make_shared<dae::GameObject>();
			auto pController = std::make_shared<dae::TextureComponent>(pControllerControls.get());
			pController->SetTexture("Controls/ControllerInput.png");
			pControllerControls->SetRelativePosition((m_Width - (m_Width/4)) - pController->GetSize().x, 300);
			pControllerControls->AddComponent(pController);
			scene.Add(pControllerControls);

			auto pTabIcon = std::make_shared<dae::GameObject>();
			auto pTab = std::make_shared<dae::TextureComponent>(pTabIcon.get());
			pTab->SetTexture("Controls/TabIcon.png");
			pTabIcon->AddComponent(pTab);
			pTabIcon->SetRelativePosition(40, 90);
			scene.Add(pTabIcon);

			auto pEAccept = std::make_shared<dae::GameObject>();
			auto pE = std::make_shared<dae::TextureComponent>(pEAccept.get());
			pE->SetTexture("Controls/EAcceptIcon.png");
			pEAccept->AddComponent(pE);
			pEAccept->SetRelativePosition(40 + pTab->GetSize().x/2 - pE->GetSize().x /2, 140);
			scene.Add(pEAccept);
		}

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto GameType = std::make_shared<GameObject>();
		auto GameTypeText = std::make_shared<TextComponent>("GameMode:", font, GameType.get());
		GameType->SetRelativePosition(m_Width/2 - 100, 90);
		GameType->AddComponent(GameTypeText);
		scene.Add(GameType);

		m_pGameModeDisplay = std::make_shared<GameObject>();
		m_pGameModeDisplayText = std::make_shared<TextComponent>("Single", font, m_pGameModeDisplay.get());
		m_pGameModeDisplay->AddComponent(m_pGameModeDisplayText);
		m_pGameModeDisplay->SetRelativePosition(m_Width / 2 - 100, 140);

		scene.Add(m_pGameModeDisplay);
		
		std::shared_ptr<GameCommands::SwitchGameMode> Switch = std::make_shared<GameCommands::SwitchGameMode>(GameObjBackGround, m_pGameModeDisplay.get(), m_CurrentScreen, this);
		std::shared_ptr<GameCommands::AcceptGameMode> Accept = std::make_shared<GameCommands::AcceptGameMode>(GameObjBackGround, this);

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, Switch);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_E, Accept);


		dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystem>());
		dae::servicelocator::get_sound_system().Load(0, "GamePlaySound.wav");
		dae::servicelocator::get_sound_system().Load(1, "PickupSound.wav");
		dae::servicelocator::get_sound_system().Load(2, "MoneyBagBreaking.wav");
		
	}

	void dae::ScreenManager::CreateGameScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Game");

		auto GameObjBackGround = std::make_shared<dae::GameObject>();
		auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
		go->SetTexture("background.png");
		GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
		GameObjBackGround->AddComponent(go);
		scene.Add(GameObjBackGround);

		auto GameObjLogo = std::make_shared<dae::GameObject>();
		auto go2 = std::make_shared<dae::TextureComponent>(GameObjLogo.get());
		go2->SetTexture("logo.tga");
		GameObjLogo->SetRelativePosition(glm::vec3{ 216, 420, 0 });
		GameObjLogo->AddComponent(go2);
		scene.Add(GameObjLogo);

		auto textObj = std::make_shared<dae::GameObject>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto to = std::make_shared<dae::TextComponent>("Programming 4 Exam", font, textObj.get());
		textObj->SetRelativePosition(glm::vec3{ 100, 20, 0 });
		textObj->AddComponent(to);
		scene.Add(textObj);

		auto GameObjFps = std::make_shared<dae::GameObject>();
		auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
		GameObjFps->SetRelativePosition(glm::vec3{ 0, 0, 0 });
		GameObjFps->AddComponent(fpsCounter);
		scene.Add(GameObjFps);

		//Mute sound
		std::shared_ptr<GameCommands::MuteMusic> muteMusic = std::make_shared<GameCommands::MuteMusic>();
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_F2, muteMusic);


		if(m_CurrentScreen == GameMode::SinglePlayer)
		{
			if (m_CurrentLevel == 0)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level.txt");

				auto pPlayer = std::make_shared<PlayerOne>(scene, pLevel->GetSpawnPosition()[0], GameObjBackGround, pLevel.get(), true);

				auto pEnemySpawn = std::make_shared<EnemySpawner>(scene, pLevel->GetEnemySpawnPosition(), 3);

				auto pWinLoseChecker = std::make_shared<dae::GameObject>();
				auto pTheChecker = std::make_shared<GameWinLosConditionComponent>(pWinLoseChecker.get(), pEnemySpawn->getSpawnObj());
				pWinLoseChecker->AddComponent(pTheChecker);

				scene.Add(pWinLoseChecker);
			}

			if (m_CurrentLevel == 1)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_01.txt");

				auto pPlayer = std::make_shared<PlayerOne>(scene, pLevel->GetSpawnPosition()[0], GameObjBackGround, pLevel.get(), true);

				auto pEnemySpawn = std::make_shared<EnemySpawner>(scene, pLevel->GetEnemySpawnPosition(), 3);

				auto pWinLoseChecker = std::make_shared<dae::GameObject>();
				auto pTheChecker = std::make_shared<GameWinLosConditionComponent>(pWinLoseChecker.get(), pEnemySpawn->getSpawnObj());
				pWinLoseChecker->AddComponent(pTheChecker);

				scene.Add(pWinLoseChecker);
			}

			if (m_CurrentLevel == 3)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_02.txt");

				auto pPlayer = std::make_shared<PlayerOne>(scene, pLevel->GetSpawnPosition()[0], GameObjBackGround, pLevel.get(), true);

				auto pEnemySpawn = std::make_shared<EnemySpawner>(scene, pLevel->GetEnemySpawnPosition(), 3);

				auto pWinLoseChecker = std::make_shared<dae::GameObject>();
				auto pTheChecker = std::make_shared<GameWinLosConditionComponent>(pWinLoseChecker.get(), pEnemySpawn->getSpawnObj());
				pWinLoseChecker->AddComponent(pTheChecker);

				scene.Add(pWinLoseChecker);
			}
		}
		
		if (m_CurrentScreen == GameMode::Coop)
		{
			//Level
			auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level.txt");

			auto pPlayer = std::make_shared<PlayerOne>(scene, pLevel->GetSpawnPosition()[0], GameObjBackGround, pLevel.get(), false);
			auto pPlayerSecond = std::make_shared<PlayerTwo>(scene, pLevel->GetSpawnPosition()[1], GameObjBackGround, true);
		}

		if (m_CurrentScreen == GameMode::Versus)
		{
			//Level
			auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level.txt");

			auto pPlayer = std::make_shared<PlayerOne>(scene, pLevel->GetSpawnPosition()[0], GameObjBackGround, pLevel.get(), false);
			auto pPlayerSecond = std::make_shared<PlayerTwo>(scene, pLevel->GetSpawnPosition()[1], GameObjBackGround, false);
		}
	}

	void ScreenManager::CreateGameOverScreen()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("GameOver");

		auto GameObjBackGround = std::make_shared<dae::GameObject>();
		auto go = std::make_shared<dae::TextureComponent>(GameObjBackGround.get());
		go->SetTexture("background.png");
		GameObjBackGround->SetRelativePosition(GameObjBackGround->GetWorldPosition());
		GameObjBackGround->AddComponent(go);
		scene.Add(GameObjBackGround);

		auto GameObjLogo = std::make_shared<dae::GameObject>();
		auto go2 = std::make_shared<dae::TextureComponent>(GameObjLogo.get());
		go2->SetTexture("logo.tga");
		GameObjLogo->SetRelativePosition(glm::vec3{ 216, 420, 0 });
		GameObjLogo->AddComponent(go2);
		scene.Add(GameObjLogo);

		const auto pMainObj = std::make_shared<dae::GameObject>();
		scene.Add(pMainObj);

		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto smallFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 22);

		const auto gameOverObj = std::make_shared<dae::GameObject>();
		const auto gameOverText = std::make_shared<dae::TextComponent>("GAME OVER", font, gameOverObj.get());
		gameOverObj->SetRelativePosition({ 200, 40 });
		gameOverObj->AddComponent(gameOverText);
		pMainObj->AddChild(gameOverObj);

		const auto resetObj = std::make_shared<dae::GameObject>("Explanation");
		const auto resetText = std::make_shared<dae::TextComponent>("Enter name (Press Enter when done)", smallFont, resetObj.get());
		resetObj->SetRelativePosition({ 160, 100 });
		resetObj->AddComponent(resetText);
		pMainObj->AddChild(resetObj);

		const auto highObj = std::make_shared<dae::GameObject>();
		const auto highText = std::make_shared<dae::TextComponent>("HighScores: ", smallFont, highObj.get());
		highObj->SetRelativePosition({ 350, 145 });
		highObj->AddComponent(highText);
		pMainObj->AddChild(highObj);

		const auto pointsObj = std::make_shared<dae::GameObject>();
		const auto pointsText = std::make_shared<dae::TextComponent>("Points: ", smallFont, pointsObj.get());
		pointsObj->SetRelativePosition({ 10, 250 });
		pointsObj->AddComponent(pointsText);
		pMainObj->AddChild(pointsObj);


		const auto scoreObj = std::make_shared<dae::GameObject>();
		scoreObj->SetTag("Score");

		scene.Add(pMainObj);

		/*
		const auto p = PlayerManager::GetInstance().GetPlayers()[0];
		const int score = p->GetComponent<PointsCp>()->GetAmount();

		const auto scoreText = std::make_shared<dae::TextComponent>(scoreObj.get(), std::to_string(score), smallFont, SDL_Color{ 255, 255, 255, 255 });
		scoreObj->SetRelativePos({ 90, 250 });
		scoreObj->AddComponent(scoreText);
		pMainObj->AddChild(scoreObj);


		const auto pNameObj = std::make_shared<dae::GameObject>();
		const auto pNameTest = std::make_shared<HighScoresCp>(pNameObj.get(), smallFont, SDL_Color{ 255, 0, 0, 255 });
		pNameObj->AddComponent(pNameTest);
		pNameObj->SetRelativePos({ 160, 250 });
		pMainObj->AddChild(pNameObj);


		//HighScores
		auto miniFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
		glm::vec2 pos{ 350, 190 };
		for (int i{}; i < 10; ++i)
		{
			const auto o = std::make_shared<dae::GameObject>();
			const std::string text = " ";
			const auto t = std::make_shared<dae::TextComponent>(o.get(), text, miniFont, SDL_Color{ 255, 255, 50, 255 });
			o->AddComponent(t);
			o->SetTag("HighScore" + std::to_string(i));
			o->SetRelativePos(pos);
			pMainObj->AddChild(o);
			pos.y += 25;
		}
		*/

	}

	void ScreenManager::CreateAppropriateGameModeScreen()
	{
		dae::servicelocator::get_sound_system().playMusic(0, 10);

		CreateGameScreen();

	}

}