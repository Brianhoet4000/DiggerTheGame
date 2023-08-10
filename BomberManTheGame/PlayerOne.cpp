#include "PlayerOne.h"
#include <SDL_scancode.h>
#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>
#include "Counter.h"
#include "GameCommands.h"
#include "Observer.h"
#include "ResourceManager.h"
#include "ShootingDirComponent.h"
#include "UIComponent.h"

dae::PlayerOne::PlayerOne(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, LevelPrefab* level, bool ControllerEnabled)
{
	auto pPlayerOne = std::make_shared<dae::GameObject>("Player_01");
	pPlayerOne->SetRelativePosition(PlayerStartPos);

	//Texture
	auto pTexture = std::make_shared<dae::TextureComponent>(pPlayerOne.get());
	pTexture->SetTexture("Sprites/Player.png");
	pPlayerOne->AddComponent(pTexture);

	//Collision
	auto pCollider = std::make_shared<dae::GameCollisionComponent>(pPlayerOne.get());
	pPlayerOne->AddComponent(pCollider);
	pCollider->SetCollisionRectOffset(5.f);
	pCollider->SetRenderCollisionBox(false);

	//BulletTimer
	auto pTimer = std::make_shared<dae::BulletTimerComponent>(pPlayerOne.get());
	pPlayerOne->AddComponent(pTimer);

	//ShootingDir
	auto pShootingDir = std::make_shared<ShootingDirComponent>();
	pPlayerOne->AddComponent(pShootingDir);
	

	//Movement
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(pPlayerOne.get(), up, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(pPlayerOne.get(), down, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(pPlayerOne.get(), left, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(pPlayerOne.get(), right, true);
	std::shared_ptr<GameCommands::ShootingBullet> ShootCommand = std::make_shared<GameCommands::ShootingBullet>(pPlayerOne.get(),&scene);
	std::shared_ptr<GameCommands::SkipLevel> SkipLevel = std::make_shared<GameCommands::SkipLevel>(pPlayerOne.get(), &scene, level);

	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_W, moveCommandUp);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_S, moveCommandDown);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_A, moveCommandLeft);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_D, moveCommandRight);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_SPACE, ShootCommand);
	dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_Q, SkipLevel);

	if(ControllerEnabled)
	{
		int controller1Index{ 0 };
		dae::InputManager::GetInstance().AddController(controller1Index);

		dae::Controller::ControllerButton controllerButton{};

		controllerButton = dae::Controller::ControllerButton::DpadUp;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUp);
		controllerButton = dae::Controller::ControllerButton::DpadDown;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDown);
		controllerButton = dae::Controller::ControllerButton::DpadLeft;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeft);
		controllerButton = dae::Controller::ControllerButton::DpadRight;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRight);
		controllerButton = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, ShootCommand);
	}

	auto pHealth = std::make_shared<dae::HealthComponent>(pPlayerOne.get(), 4);
	pPlayerOne->AddComponent(pHealth);

	auto pPoints = std::make_shared<dae::PointsComponent>(pPlayerOne.get(), 0);
	pPlayerOne->AddComponent(pPoints);

	//std::shared_ptr<HealthCommand> dieCommand = std::make_shared<HealthCommand>(GameObjBomberman.get());
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	pPlayerOne->MakeObserver(pUIObserver);

	//Lives Display
	auto PlayerOneLives = std::make_shared<dae::GameObject>("Player_01");
	auto fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
		"Lives", PlayerOneLives.get());
	PlayerOneLives->SetRelativePosition({ 5, 340 });
	PlayerOneLives->AddComponent(textBomberManLives);
	background->AddChild(PlayerOneLives);
	scene.Add(PlayerOneLives);

	//Points Display
	auto PlayerOnePoints = std::make_shared<dae::GameObject>("Player_01");
	auto textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
		"Points", PlayerOnePoints.get());
	PlayerOnePoints->SetRelativePosition({ 5, 360 });
	PlayerOnePoints->AddComponent(textBluePoints);
	background->AddChild(PlayerOnePoints);
	scene.Add(PlayerOnePoints);


	scene.Add(pPlayerOne);
}
