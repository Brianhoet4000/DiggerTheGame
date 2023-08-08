#include "PlayerTwo.h"

#include <algorithm>
#include <SDL_scancode.h>

#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>

#include "CollisionBoxComponent.h"
#include "Counter.h"
#include "GameCommands.h"
#include "HobbinComponent.h"
#include "Observer.h"
#include "ResourceManager.h"
#include "ShootingDirComponent.h"
#include "UIComponent.h"

dae::PlayerTwo::PlayerTwo(dae::Scene& scene, glm::vec2 PlayerStartPos, std::shared_ptr<GameObject> background, bool Coop)
{
	auto PlayerTwo = std::make_shared<dae::GameObject>("Player_02");
	PlayerTwo->SetRelativePosition(PlayerStartPos);

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
		auto TexturePlayerTwo = std::make_shared<dae::TextureComponent>(PlayerTwo.get());
		TexturePlayerTwo->SetTexture("Sprites/Player1.png");
		PlayerTwo->AddComponent(TexturePlayerTwo);

		//Collision
		auto Collider = std::make_shared<dae::GameCollisionComponent>(PlayerTwo.get());
		Collider->SetCollisionRectOffset(5.f);
		PlayerTwo->AddComponent(Collider);

		//ShootingDir
		auto shootingDir = std::make_shared<ShootingDirComponent>();
		PlayerTwo->AddComponent(shootingDir);

		//Movement
		moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), up, true);
		moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), down, true);
		moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), left, true);
		moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), right, true);



		std::shared_ptr<GameCommands::ShootingBullet> ShootCommand = std::make_shared<GameCommands::ShootingBullet>(PlayerTwo.get(), &scene);
		controllerButton = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, ShootCommand);
	}
	else
	{
		//Texture Verus
		auto TexturePlayerTwo = std::make_shared<dae::TextureComponent>(PlayerTwo.get());
		TexturePlayerTwo->SetTexture("Sprites/Nobbin.png");
		PlayerTwo->AddComponent(TexturePlayerTwo);

		//Collision
		auto Collider = std::make_shared<dae::GameCollisionComponent>(PlayerTwo.get(), true);
		Collider->SetRenderCollisionBox(false);
		PlayerTwo->AddComponent(Collider);

		auto Hobbin = std::make_shared<dae::HobbinComponent>(PlayerTwo.get());
		PlayerTwo->AddComponent(Hobbin);

		moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), up, false);
		moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), down, false);
		moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), left, false);
		moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(PlayerTwo.get(), right, false);
	}


	controllerButton = dae::Controller::ControllerButton::DpadUp;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUp);
	controllerButton = dae::Controller::ControllerButton::DpadDown;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDown);
	controllerButton = dae::Controller::ControllerButton::DpadLeft;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeft);
	controllerButton = dae::Controller::ControllerButton::DpadRight;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRight);

	auto pHealth = std::make_shared<dae::HealthComponent>(PlayerTwo.get(), 4);
	PlayerTwo->AddComponent(pHealth);

	auto pPoints = std::make_shared<dae::PointsComponent>(PlayerTwo.get(), 0);
	PlayerTwo->AddComponent(pPoints);

	//HealthCommand* dieCommand = new HealthCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);

	auto pUIObserver = std::make_shared<UI>();
	PlayerTwo->MakeObserver(pUIObserver);

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


	scene.Add(PlayerTwo);
}
