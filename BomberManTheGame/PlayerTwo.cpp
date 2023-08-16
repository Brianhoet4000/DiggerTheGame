#include "PlayerTwo.h"
#include <algorithm>
#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>
#include "Counter.h"
#include "GameCommands.h"
#include "HobbinComponent.h"
#include "Observer.h"
#include "ResourceManager.h"
#include "ShootingDirComponent.h"
#include "UIComponent.h"

dae::PlayerTwo::PlayerTwo(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, bool Coop)
{
	auto pPlayerTwo = std::make_shared<dae::GameObject>("Player_02");
	pPlayerTwo->SetRelativePosition(PlayerStartPos);

	std::shared_ptr<GameCommands::DiggerMovement> moveCommandUp;
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandDown;
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandLeft;
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandRight;

	int controller1Index{ 0 };
	dae::InputManager::GetInstance().AddController(controller1Index);

	dae::Controller::ControllerButton controllerButton{};

	if (Coop)
	{
		//Texture Coop
		auto pTexture = std::make_shared<dae::TextureComponent>(pPlayerTwo.get());
		pTexture->SetTexture("Sprites/Player1.png");
		pPlayerTwo->AddComponent(pTexture);

		//Collision
		auto pCollider = std::make_shared<dae::GameCollisionComponent>(pPlayerTwo.get());
		pCollider->SetCollisionRectOffset(5.f);
		pPlayerTwo->AddComponent(pCollider);

		//BulletTimer
		auto pTimer = std::make_shared<dae::BulletTimerComponent>(pPlayerTwo.get());
		pPlayerTwo->AddComponent(pTimer);

		//ShootingDir
		auto pShootingDir = std::make_shared<ShootingDirComponent>();
		pPlayerTwo->AddComponent(pShootingDir);

		//Movement
		moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Up, true);
		moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Down, true);
		moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Left, true);
		moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Right, true);



		std::shared_ptr<GameCommands::ShootingBullet> ShootCommand = std::make_shared<GameCommands::ShootingBullet>(pPlayerTwo, &scene);
		controllerButton = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, ShootCommand);
	}
	else
	{
		m_Speed = 75;
		//Texture Verus
		auto pTexture = std::make_shared<dae::TextureComponent>(pPlayerTwo.get());
		pTexture->SetTexture("Sprites/Nobbin.png");
		pPlayerTwo->AddComponent(pTexture);

		//Collision
		auto pCollider = std::make_shared<dae::GameCollisionComponent>(pPlayerTwo.get(), true);
		pCollider->SetRenderCollisionBox(false);
		pPlayerTwo->AddComponent(pCollider);

		auto Hobbin = std::make_shared<dae::HobbinComponent>(pPlayerTwo.get());
		pPlayerTwo->AddComponent(Hobbin);

		moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Up, false);
		moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Down, false);
		moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Left, false);
		moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(pPlayerTwo, m_Right, false);
	}


	controllerButton = dae::Controller::ControllerButton::DpadUp;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUp);
	controllerButton = dae::Controller::ControllerButton::DpadDown;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDown);
	controllerButton = dae::Controller::ControllerButton::DpadLeft;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeft);
	controllerButton = dae::Controller::ControllerButton::DpadRight;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRight);

	auto pHealth = std::make_shared<dae::HealthComponent>(pPlayerTwo.get(), 4);
	pPlayerTwo->AddComponent(pHealth);

	auto pPoints = std::make_shared<dae::PointsComponent>(pPlayerTwo.get(), 0);
	pPlayerTwo->AddComponent(pPoints);

	//HealthCommand* dieCommand = new HealthCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	pPlayerTwo->MakeObserver(pUIObserver);

	//Lives Display
	auto PlayerTwoLives = std::make_shared<dae::GameObject>("Player_02");
	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		"Lives", PlayerTwoLives.get());
	PlayerTwoLives->SetRelativePosition({ 5, 400 });
	PlayerTwoLives->AddComponent(textBomberManLives);
	background->AddChild(PlayerTwoLives);
	scene.Add(PlayerTwoLives);

	//Points Display
	auto PlayerTwoPoints = std::make_shared<dae::GameObject>("Player_02");
	auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		"Points", PlayerTwoPoints.get());
	PlayerTwoPoints->SetRelativePosition({ 5, 420 });	
	PlayerTwoPoints->AddComponent(textBluePoints);
	background->AddChild(PlayerTwoPoints);
	scene.Add(PlayerTwoPoints);


	scene.Add(pPlayerTwo);
}
