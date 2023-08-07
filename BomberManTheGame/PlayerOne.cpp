#include "PlayerOne.h"

#include <SDL_scancode.h>

#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>

#include "CollisionBoxComponent.h"
#include "Counter.h"
#include "GameCommands.h"
#include "Observer.h"
#include "ResourceManager.h"
#include "ShootingDirComponent.h"
#include "UIComponent.h"

dae::PlayerOne::PlayerOne(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, LevelPrefab* level, bool ControllerEnabled)
{
	auto PlayerOne = std::make_shared<dae::GameObject>("Player_01");
	PlayerOne->SetRelativePosition(PlayerStartPos);

	//Texture
	auto PlayerOneTex = std::make_shared<dae::TextureComponent>(PlayerOne.get());
	PlayerOneTex->SetTexture("Sprites/Player.png");
	PlayerOne->AddComponent(PlayerOneTex);

	//Collision
	auto Collider = std::make_shared<dae::GameCollisionComponent>(PlayerOne.get());
	PlayerOne->AddComponent(Collider);
	Collider->SetCollisionRectOffset(5.f);
	Collider->SetRenderCollisionBox(true);

	//ShootingDir
	auto shootingDir = std::make_shared<ShootingDirComponent>();
	PlayerOne->AddComponent(shootingDir);
	

	//Movement
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(PlayerOne.get(), up, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(PlayerOne.get(), down, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(PlayerOne.get(), left, true);
	std::shared_ptr<GameCommands::DiggerMovement> moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(PlayerOne.get(), right, true);
	std::shared_ptr<GameCommands::ShootingBullet> ShootCommand = std::make_shared<GameCommands::ShootingBullet>(PlayerOne.get(),&scene);
	std::shared_ptr<GameCommands::SkipLevel> SkipLevel = std::make_shared<GameCommands::SkipLevel>(PlayerOne.get(), &scene, level);

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
	}

	auto pHealth = std::make_shared<dae::HealthComponent>(PlayerOne.get(), 4);
	PlayerOne->AddComponent(pHealth);

	auto pPoints = std::make_shared<dae::PointsComponent>(PlayerOne.get(), 0);
	PlayerOne->AddComponent(pPoints);

	//std::shared_ptr<HealthCommand> dieCommand = std::make_shared<HealthCommand>(GameObjBomberman.get());
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	PlayerOne->MakeObserver(pUIObserver);

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


	scene.Add(PlayerOne);
}
