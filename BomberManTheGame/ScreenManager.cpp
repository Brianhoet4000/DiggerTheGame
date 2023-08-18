#include "ScreenManager.h"
#include <SDL_scancode.h>
#include <glm/vec2.hpp>
#include "EnemyPrefab.h"
#include "EnemySpawner.h"
#include "GameCommands.h"
#include "FPSCounterComponent.h"
#include "GameWinLosConditionComponent.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"

namespace dae
{

	void dae::ScreenManager::CreateMenuScreen(dae::Scene& scene)
	{
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
		
		std::shared_ptr<GameCommands::SwitchGameMode> Switch = std::make_shared<GameCommands::SwitchGameMode>(GameObjBackGround, m_pGameModeDisplay.get(), m_CurrentGameMode, this);
		std::shared_ptr<GameCommands::AcceptGameMode> Accept = std::make_shared<GameCommands::AcceptGameMode>();
		std::shared_ptr<GameCommands::SkipLevel> SkipLevel = std::make_shared<GameCommands::SkipLevel>();
		std::shared_ptr<GameCommands::ResetLevel> ResetLevel = std::make_shared<GameCommands::ResetLevel>();

		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_TAB, Switch);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_E, Accept);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_Q, SkipLevel);
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_R, ResetLevel);

		dae::servicelocator::register_sound_system(std::make_unique<dae::SoundSystem>());
		dae::servicelocator::get_sound_system().Load(0, "GamePlaySound.wav");
		dae::servicelocator::get_sound_system().Load(1, "PickupSound.wav");
		dae::servicelocator::get_sound_system().Load(2, "MoneyBagBreaking.wav");
	}

	void dae::ScreenManager::CreateGameScreen(dae::Scene& scene)
	{
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


		auto GameObjFps = std::make_shared<dae::GameObject>();
		auto fpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		auto fpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", fpsFont, GameObjFps.get());
		GameObjFps->SetRelativePosition(glm::vec3{ 0, 0, 0 });
		GameObjFps->AddComponent(fpsCounter);
		scene.Add(GameObjFps);

		//Mute sound
		std::shared_ptr<GameCommands::MuteMusic> muteMusic = std::make_shared<GameCommands::MuteMusic>();
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_F2, muteMusic);

		/*
		switch (m_CurrentGameMode)
		{
		case SinglePlayer:

			switch(m_CurrentLevel)
			{
			case 0:

				break;

			case 1:
				break;

			case 2:
				break;
			}
			break;

		case Coop:

			switch (m_CurrentLevel)
			{
			case 0:
				break;

			case 1:
				break;

			case 2:
				break;
			}
			break;

		case Versus:

			switch (m_CurrentLevel)
			{
			case 0:
				break;

			case 1:
				break;

			case 2:
				break;
			}
			break;
		}

		*/

		if(m_CurrentGameMode == GameMode::SinglePlayer)
		{
			if (m_CurrentLevel == 0)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_0.txt");

				auto player = PlayerManager::GetInstance().GetPlayers();
				dae::SceneManager::GetInstance().GetActiveScene()->Add(player[0]);
				player[0]->SetRelativePosition(pLevel->GetSpawnPosition()[0]);

				auto pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 3);
			}

			if (m_CurrentLevel == 1)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_1.txt");

				//auto EnemySpawner = std::make_shared<dae::EnemySpawner>(scene, pLevel->GetEnemySpawnPosition(), 4);
				auto player = PlayerManager::GetInstance().GetPlayers();
				dae::SceneManager::GetInstance().GetActiveScene()->Add(player[0]);
				player[0]->SetRelativePosition(pLevel->GetSpawnPosition()[0]);

				auto pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 5);
			}

			if (m_CurrentLevel == 2)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_2.txt");

				//auto EnemySpawner = std::make_shared<dae::EnemySpawner>(scene, pLevel->GetEnemySpawnPosition(), 6);
				auto player = PlayerManager::GetInstance().GetPlayers();
				dae::SceneManager::GetInstance().GetActiveScene()->Add(player[0]);
				player[0]->SetRelativePosition(pLevel->GetSpawnPosition()[0]);

				auto pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 7);
			}
		}
		
		if (m_CurrentGameMode == GameMode::Coop)
		{
			if (m_CurrentLevel == 0)
			{
				auto Player_02 = std::make_shared<dae::PlayerTwo>(scene, true);
				PlayerManager::GetInstance().AddPlayer(Player_02->ReturnPlayer());

				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_0.txt");


				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				auto pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 6);
			}

			if (m_CurrentLevel == 1)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_1.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				auto pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 12);
			}

			if (m_CurrentLevel == 2)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_2.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				auto pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 15);
			}
			
		}

		if (m_CurrentGameMode == GameMode::Versus)
		{
			if (m_CurrentLevel == 0)
			{
				auto Player_02 = std::make_shared<dae::PlayerTwo>(scene, false);
				PlayerManager::GetInstance().AddPlayer(Player_02->ReturnPlayer());

				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_0.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

			}

			if (m_CurrentLevel == 1)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_1.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}
			}

			if (m_CurrentLevel == 2)
			{
				//Level
				auto pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_2.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}
			}
		}
		

		IncrementCurrentLevel();
	}

	void ScreenManager::CreateGameOverScreen(dae::Scene& scene)
	{
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
			const auto t = std::make_shared<dae::TextComponent>(text, miniFont, o.get());
			o->AddComponent(t);
			o->SetTag("HighScore" + std::to_string(i));
			o->SetRelativePosition(pos);
			pMainObj->AddChild(o);
			pos.y += 25;
		}
		*/

	}

	void ScreenManager::CreateAppropriateGameModeScreen()
	{
		dae::servicelocator::get_sound_system().playMusic(0, 10);

		//CreateGameScreen();

	}

}