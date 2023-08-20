#include "ScreenManager.h"
#include <SDL_scancode.h>
#include <glm/vec2.hpp>
#include "EnemyPrefab.h"
#include "EnemySpawner.h"
#include "Font.h"
#include "GameCommands.h"
#include "FPSCounterComponent.h"
#include "GameCollisionMngr.h"
#include "ConditionSingleCoopComponent.h"
#include "ConditionVersusComponent.h"
#include "HealthComponent.h"
#include "HighscoreComponent.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "PointComponent.h"

namespace dae
{

	void dae::ScreenManager::CreateMenuScreen(dae::Scene& scene)
	{
		m_pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

		const auto& pGameObjBackGround = std::make_shared<dae::GameObject>();
		const auto& pBackGroundLogo = std::make_shared<dae::TextureComponent>(pGameObjBackGround.get());
		pBackGroundLogo->SetTexture("background.png");
		pGameObjBackGround->SetRelativePosition(pGameObjBackGround->GetWorldPosition());
		pGameObjBackGround->AddComponent(pBackGroundLogo);
		scene.Add(pGameObjBackGround);

		//Controls
		{
			const auto& pKeyboardControls = std::make_shared<dae::GameObject>();
			const auto& pKeyboard = std::make_shared<dae::TextureComponent>(pKeyboardControls.get());
			pKeyboard->SetTexture("Controls/WASDSpace.png");
			pKeyboardControls->SetRelativePosition(m_Width / 6, 300);
			pKeyboardControls->AddComponent(pKeyboard);
			scene.Add(pKeyboardControls);

			const auto& pControllerControls = std::make_shared<dae::GameObject>();
			const auto& pController = std::make_shared<dae::TextureComponent>(pControllerControls.get());
			pController->SetTexture("Controls/ControllerInput.png");
			pControllerControls->SetRelativePosition((m_Width - (m_Width/4)) - pController->GetSize().x, 300);
			pControllerControls->AddComponent(pController);
			scene.Add(pControllerControls);

			const auto& pTabIcon = std::make_shared<dae::GameObject>();
			const auto& pTab = std::make_shared<dae::TextureComponent>(pTabIcon.get());
			pTab->SetTexture("Controls/TabIcon.png");
			pTabIcon->AddComponent(pTab);
			pTabIcon->SetRelativePosition(40, 90);
			scene.Add(pTabIcon);

			const auto& pEAccept = std::make_shared<dae::GameObject>();
			const auto& pE = std::make_shared<dae::TextureComponent>(pEAccept.get());
			pE->SetTexture("Controls/EAcceptIcon.png");
			pEAccept->AddComponent(pE);
			pEAccept->SetRelativePosition(40 + pTab->GetSize().x/2 - pE->GetSize().x /2, 140);
			scene.Add(pEAccept);
		}

		const auto& pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		const auto& pGameType = std::make_shared<GameObject>();
		const auto& pGameTypeText = std::make_shared<TextComponent>("GameMode:", pFont, pGameType.get());
		pGameType->SetRelativePosition(m_Width/2 - 100, 90);
		pGameType->AddComponent(pGameTypeText);
		scene.Add(pGameType);

		m_pGameModeDisplay = std::make_shared<GameObject>();
		m_pGameModeDisplayText = std::make_shared<TextComponent>("Single", pFont, m_pGameModeDisplay.get());
		m_pGameModeDisplay->AddComponent(m_pGameModeDisplayText);
		m_pGameModeDisplay->SetRelativePosition(m_Width / 2 - 100, 140);

		scene.Add(m_pGameModeDisplay);
		
		std::shared_ptr<GameCommands::SwitchGameMode> Switch = std::make_shared<GameCommands::SwitchGameMode>(pGameObjBackGround, m_pGameModeDisplay.get(), m_CurrentGameMode, this);
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
		const auto& pGameObjBackGround = std::make_shared<dae::GameObject>();
		const auto& pBackGroundLogo = std::make_shared<dae::TextureComponent>(pGameObjBackGround.get());
		pBackGroundLogo->SetTexture("background.png");
		pGameObjBackGround->SetRelativePosition(pGameObjBackGround->GetWorldPosition());
		pGameObjBackGround->AddComponent(pBackGroundLogo);
		scene.Add(pGameObjBackGround);

		const auto& pGameObjLogo = std::make_shared<dae::GameObject>();
		const auto& pDaeLogo = std::make_shared<dae::TextureComponent>(pGameObjLogo.get());
		pDaeLogo->SetTexture("logo.tga");
		pGameObjLogo->SetRelativePosition(m_Width/2 - pDaeLogo->GetSize().x/2, 420);
		pGameObjLogo->AddComponent(pDaeLogo);
		scene.Add(pGameObjLogo);

		const auto& pGameObjFps = std::make_shared<dae::GameObject>();
		const auto& pFpsFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
		const auto& pFpsCounter = std::make_shared<dae::FPSCounterComponent>("FPS", pFpsFont, pGameObjFps.get());
		pGameObjFps->SetRelativePosition(0, 0);
		pGameObjFps->AddComponent(pFpsCounter);
		scene.Add(pGameObjFps);

		//Player One
		{
			const auto& pGameObjLivesText = std::make_shared<dae::GameObject>();
			const auto& pLivesText = std::make_shared<dae::TextComponent>("Lives:", m_pFont, pGameObjLivesText.get());
			pGameObjLivesText->SetRelativePosition(10, 410);
			pGameObjLivesText->AddComponent(pLivesText);
			scene.Add(pGameObjLivesText);

			const auto& pGameObjPointText = std::make_shared<dae::GameObject>();
			const auto& pPointsText = std::make_shared<dae::TextComponent>("Points:", m_pFont, pGameObjPointText.get());
			pGameObjPointText->SetRelativePosition(10, 430);
			pGameObjPointText->AddComponent(pPointsText);
			scene.Add(pGameObjPointText);
		}
		//Player Two
		{
			const auto& pGameObjLivesText = std::make_shared<dae::GameObject>();
			const auto& pLivesText = std::make_shared<dae::TextComponent>("Lives:", m_pFont, pGameObjLivesText.get());
			pGameObjLivesText->SetRelativePosition(120, 410);
			pGameObjLivesText->AddComponent(pLivesText);
			scene.Add(pGameObjLivesText);

			const auto& pGameObjPointText = std::make_shared<dae::GameObject>();
			const auto& pPointsText = std::make_shared<dae::TextComponent>("Points:", m_pFont, pGameObjPointText.get());
			pGameObjPointText->SetRelativePosition(120, 430);
			pGameObjPointText->AddComponent(pPointsText);
			scene.Add(pGameObjPointText);
		}

		//Mute sound
		std::shared_ptr<GameCommands::MuteMusic> muteMusic = std::make_shared<GameCommands::MuteMusic>();
		dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_F2, muteMusic);

		CreateLevelZero(scene);
		CreateLevelOne(scene);
		CreateLevelTwo(scene);
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
		highObj->SetRelativePosition({ 300, 145 });
		highObj->AddComponent(highText);
		pMainObj->AddChild(highObj);

		const auto pointsObj = std::make_shared<dae::GameObject>();
		const auto pointsText = std::make_shared<dae::TextComponent>("Points: ", smallFont, pointsObj.get());
		pointsObj->SetRelativePosition({ 10, 250 });
		pointsObj->AddComponent(pointsText);
		pMainObj->AddChild(pointsObj);

		const auto scoreObj = std::make_shared<dae::GameObject>();
		scoreObj->SetTag("Score");
		scoreObj->SetRelativePosition({ 90, 250 });

		const auto pp = std::make_shared<dae::HighscoreComponent>(scoreObj.get(), smallFont);
		scoreObj->AddComponent(pp);
		pMainObj->AddChild(scoreObj);

		scene.Add(pMainObj);
	}

	void ScreenManager::CreateLevelZero(dae::Scene& scene)
	{
		if(m_CurrentLevel == 0)
		{
			if (m_CurrentGameMode == GameMode::SinglePlayer)
			{
				if (!m_AddedPlayers)
				{
					const auto& pPlayer_01 = std::make_shared<dae::PlayerOne>(scene);
					PlayerManager::GetInstance().AddPlayer(pPlayer_01->ReturnPlayer());
					m_AddedPlayers = true;
				}
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_0.txt");

				auto player = PlayerManager::GetInstance().GetPlayers();
				dae::SceneManager::GetInstance().GetActiveScene()->Add(player[0]);
				player[0]->SetRelativePosition(pLevel->GetSpawnPosition()[0]);

				const auto& pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 3);
				const auto& pWinLose = std::make_shared<dae::ConditionSingleCoopComponent>(pLevel->returnLevelObj().get(), pSpawner->getSpawnObj());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				CreateUI(scene, player, false);
			}

			else if(m_CurrentGameMode == GameMode::Coop)
			{
				if (!m_AddedPlayers)
				{
					const auto& pPlayer_01 = std::make_shared<dae::PlayerOne>(scene);
					PlayerManager::GetInstance().AddPlayer(pPlayer_01->ReturnPlayer());

					const auto& Player_02 = std::make_shared<dae::PlayerTwo>(scene, true);
					PlayerManager::GetInstance().AddPlayer(Player_02->ReturnPlayer());
					m_AddedPlayers = true;
				}

				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_0.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				const auto& pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 6);
				const auto& pWinLose = std::make_shared<dae::ConditionSingleCoopComponent>(pLevel->returnLevelObj().get(), pSpawner->getSpawnObj());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				auto players = PlayerManager::GetInstance().GetPlayers();
				CreateUI(scene, players, true);
			}

			else if(m_CurrentGameMode == GameMode::Versus)
			{
				if (!m_AddedPlayers)
				{
					const auto& pPlayer_01 = std::make_shared<dae::PlayerOne>(scene);
					PlayerManager::GetInstance().AddPlayer(pPlayer_01->ReturnPlayer());

					const auto& Player_02 = std::make_shared<dae::PlayerTwo>(scene, false);
					PlayerManager::GetInstance().AddPlayer(Player_02->ReturnPlayer());
					m_AddedPlayers = true;
				}

				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_0.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				const auto& pWinLose = std::make_shared<dae::ConditionVersusComponent>(pLevel->returnLevelObj().get());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				auto players = PlayerManager::GetInstance().GetPlayers();
				CreateUI(scene, players, true);
			}
		}
	}

	void ScreenManager::CreateLevelOne(dae::Scene& scene)
	{
		if (m_CurrentLevel == 1)
		{
			if (m_CurrentGameMode == GameMode::SinglePlayer)
			{
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_1.txt");

				auto player = PlayerManager::GetInstance().GetPlayers();
				dae::SceneManager::GetInstance().GetActiveScene()->Add(player[0]);
				player[0]->SetRelativePosition(pLevel->GetSpawnPosition()[0]);

				const auto& pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 5);
				const auto& pWinLose = std::make_shared<dae::ConditionSingleCoopComponent>(pLevel->returnLevelObj().get(), pSpawner->getSpawnObj());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				CreateUI(scene, player, false);
			}

			else if (m_CurrentGameMode == GameMode::Coop)
			{
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_1.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				const auto& pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 12);
				const auto& pWinLose = std::make_shared<dae::ConditionSingleCoopComponent>(pLevel->returnLevelObj().get(), pSpawner->getSpawnObj());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				auto players = PlayerManager::GetInstance().GetPlayers();
				CreateUI(scene, players, true);
			}

			else if (m_CurrentGameMode == GameMode::Versus)
			{
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_1.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				const auto& pWinLose = std::make_shared<dae::ConditionVersusComponent>(pLevel->returnLevelObj().get());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				auto players = PlayerManager::GetInstance().GetPlayers();
				CreateUI(scene, players, true);
			}
		}
	}

	void ScreenManager::CreateLevelTwo(dae::Scene& scene)
	{
		if (m_CurrentLevel == 2)
		{
			if (m_CurrentGameMode == GameMode::SinglePlayer)
			{
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_2.txt");

				//auto EnemySpawner = std::make_shared<dae::EnemySpawner>(scene, pLevel->GetEnemySpawnPosition(), 6);
				auto player = PlayerManager::GetInstance().GetPlayers();
				dae::SceneManager::GetInstance().GetActiveScene()->Add(player[0]);
				player[0]->SetRelativePosition(pLevel->GetSpawnPosition()[0]);

				const auto& pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 7);
				const auto& pWinLose = std::make_shared<dae::ConditionSingleCoopComponent>(pLevel->returnLevelObj().get(), pSpawner->getSpawnObj());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				CreateUI(scene, player, false);
			}

			else if (m_CurrentGameMode == GameMode::Coop)
			{
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_2.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				const auto& pSpawner = std::make_shared<dae::EnemySpawner>(*dae::SceneManager::GetInstance().GetActiveScene(), pLevel->GetEnemySpawnPosition(), 15);
				const auto& pWinLose = std::make_shared<dae::ConditionSingleCoopComponent>(pLevel->returnLevelObj().get(), pSpawner->getSpawnObj());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				auto players = PlayerManager::GetInstance().GetPlayers();
				CreateUI(scene, players, true);
			}

			else if (m_CurrentGameMode == GameMode::Versus)
			{
				//Level
				const auto& pLevel = std::make_shared<dae::LevelPrefab>(scene, "level_2.txt");

				for (int i = 0; i < static_cast<int>(PlayerManager::GetInstance().GetPlayers().size()); ++i)
				{
					dae::SceneManager::GetInstance().GetActiveScene()->Add(PlayerManager::GetInstance().GetPlayers()[i]);
					PlayerManager::GetInstance().GetPlayers()[i]->SetRelativePosition(pLevel->GetSpawnPosition()[i]);
				}

				const auto& pWinLose = std::make_shared<dae::ConditionVersusComponent>(pLevel->returnLevelObj().get());
				pLevel->returnLevelObj()->AddComponent(pWinLose);

				auto players = PlayerManager::GetInstance().GetPlayers();
				CreateUI(scene, players, true);
			}
		}
	}

	void ScreenManager::CreateUI(dae::Scene& scene, std::vector<std::shared_ptr<GameObject>>& players, bool SecondPlayer)
	{
		const auto& pPlayerLives = std::make_shared<dae::GameObject>();
		const auto& pPlayerLiveText = std::make_shared<dae::TextComponent>(std::to_string(players[0]->GetComponent<HealthComponent>()->GetAmount()),
			m_pFont, pPlayerLives.get());
		pPlayerLives->AddComponent(pPlayerLiveText);
		pPlayerLives->SetRelativePosition(60, 410);
		scene.Add(pPlayerLives);

		const auto& pPlayerPoints = std::make_shared<GameObject>("PlayerOnePoints");
		const auto& pPlayerPointsText = std::make_shared<TextComponent>(std::to_string(players[0]->GetComponent<PointComponent>()->GetAmount()),
			m_pFont, pPlayerPoints.get());
		pPlayerPoints->AddComponent(pPlayerPointsText);
		pPlayerPoints->SetRelativePosition(75, 430);
		scene.Add(pPlayerPoints);

		if(SecondPlayer)
		{
			const auto& pPlayerLives2 = std::make_shared<dae::GameObject>();
			const auto& pPlayerLiveText2 = std::make_shared<dae::TextComponent>(std::to_string(players[1]->GetComponent<HealthComponent>()->GetAmount()),
				m_pFont, pPlayerLives2.get());
			pPlayerLives2->AddComponent(pPlayerLiveText2);
			pPlayerLives2->SetRelativePosition(170, 410);
			scene.Add(pPlayerLives2);

			const auto& pPlayerPoints2 = std::make_shared<GameObject>("PlayerTwoPoints");
			const auto& pPlayerPointsText2 = std::make_shared<TextComponent>(std::to_string(players[1]->GetComponent<PointComponent>()->GetAmount()),
				m_pFont, pPlayerPoints2.get());
			pPlayerPoints2->AddComponent(pPlayerPointsText2);
			pPlayerPoints2->SetRelativePosition(185, 430);
			scene.Add(pPlayerPoints2);
		}
	}

	void ScreenManager::PlayerKilledResetLevelAndStats(dae::GameCollisionComponent* ownerbox) const
	{
		ownerbox->GetOwner()->GetComponent<HealthComponent>()->DecreaseAmount(1);
		ownerbox->GetOwner()->GetComponent<PointComponent>()->SetAmount(0);
		
		const auto& scene = dae::SceneManager::GetInstance().GetActiveScene();
		
		if (ownerbox->GetOwner()->GetTag() == "Player_01")
		{
			const auto& points = GetInstance().GetGameObjectInScene(*scene, "PlayerOnePoints");
			points->GetComponent<TextComponent>()->SetText(std::to_string(ownerbox->GetOwner()->GetComponent<PointComponent>()->GetAmount()));
		}
		else
		{
			const auto& points = GetInstance().GetGameObjectInScene(*scene, "PlayerTwoPoints");
			points->GetComponent<TextComponent>()->SetText(std::to_string(ownerbox->GetOwner()->GetComponent<PointComponent>()->GetAmount()));
		}


		dae::SceneManager::GetInstance().GetActiveScene()->RemoveAll();
		dae::GameCollisionMngr::GetInstance().ClearAll();
		GetInstance().CreateGameScreen(*SceneManager::GetInstance().GetActiveScene());


	}

	GameObject* ScreenManager::GetGameObjectInScene(dae::Scene& scene, std::string tag)
	{
		for (const auto& gameObjects : scene.GetGameObjects())
		{
			if(gameObjects->GetTag() == tag)
			{
				return gameObjects.get();
			}
		}
		return nullptr;
	}

	void ScreenManager::SkipToGameOverLevel()
	{
		switch (m_CurrentLevel)
		{
		case 0:
		{
			SceneManager::GetInstance().NextScene();
			dae::GameCollisionMngr::GetInstance().ClearAll();
			IncrementCurrentLevel();

			SceneManager::GetInstance().NextScene();
			IncrementCurrentLevel();

			SceneManager::GetInstance().NextScene();
			IncrementCurrentLevel();

			break;
		}

		case 1:
		{
			SceneManager::GetInstance().NextScene();
			dae::GameCollisionMngr::GetInstance().ClearAll();
			IncrementCurrentLevel();

			SceneManager::GetInstance().NextScene();
			dae::GameCollisionMngr::GetInstance().ClearAll();
			IncrementCurrentLevel();
			break;
		}
		case 2:
		{
			SceneManager::GetInstance().NextScene();
			dae::GameCollisionMngr::GetInstance().ClearAll();
			IncrementCurrentLevel();
			break;
		}
		}
	}

	void ScreenManager::ProceedNextLevel() const
	{
		dae::SceneManager::GetInstance().NextScene();

		if (dae::SceneManager::GetInstance().GetActiveSceneName() != "GameOver")
		{
			dae::GameCollisionMngr::GetInstance().ClearAll();
			dae::ScreenManager::GetInstance().IncrementCurrentLevel();
			dae::ScreenManager::GetInstance().CreateGameScreen(*dae::SceneManager::GetInstance().GetActiveScene());
		}
	}

}
