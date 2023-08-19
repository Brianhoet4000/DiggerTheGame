#include "PlayerTwo.h"
#include <algorithm>
#include "Commands.h"
#include "InputManager.h"
#include <TextureComponent.h>
#include "Counter.h"
#include "GameCommands.h"
#include "HobbinComponent.h"
#include "ResourceManager.h"
#include "ShootingDirComponent.h"

dae::PlayerTwo::PlayerTwo(dae::Scene& scene,  bool Coop)
{
	m_pPlayerTwo = std::make_shared<dae::GameObject>("Player_02");

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
		const auto& pTexture = std::make_shared<dae::TextureComponent>(m_pPlayerTwo.get());
		pTexture->SetTexture("Sprites/Player1.png");
		m_pPlayerTwo->AddComponent(pTexture);

		//Collision
		const auto& pCollider = std::make_shared<dae::GameCollisionComponent>(m_pPlayerTwo.get());
		pCollider->SetCollisionRectOffset(5.f);
		pCollider->SetRenderCollisionBox(true);
		m_pPlayerTwo->AddComponent(pCollider);

		//BulletTimer
		const auto& pTimer = std::make_shared<dae::BulletTimerComponent>(m_pPlayerTwo.get());
		m_pPlayerTwo->AddComponent(pTimer);

		//ShootingDir
		const auto& pShootingDir = std::make_shared<ShootingDirComponent>();
		m_pPlayerTwo->AddComponent(pShootingDir);

		//Movement
		moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Up, true);
		moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Down, true);
		moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Left, true);
		moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Right, true);

		std::shared_ptr<GameCommands::ShootingBullet> ShootCommand = std::make_shared<GameCommands::ShootingBullet>(m_pPlayerTwo, &scene);
		controllerButton = dae::Controller::ControllerButton::ButtonA;
		dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, ShootCommand);
	}
	else
	{
		m_Speed = 75;
		//Texture Verus
		const auto& pTexture = std::make_shared<dae::TextureComponent>(m_pPlayerTwo.get());
		pTexture->SetTexture("Sprites/Nobbin.png");
		m_pPlayerTwo->AddComponent(pTexture);

		//Collision
		const auto& pCollider = std::make_shared<dae::GameCollisionComponent>(m_pPlayerTwo.get(), true);
		pCollider->SetRenderCollisionBox(false);
		m_pPlayerTwo->AddComponent(pCollider);

		const auto& Hobbin = std::make_shared<dae::HobbinComponent>(m_pPlayerTwo.get());
		m_pPlayerTwo->AddComponent(Hobbin);

		moveCommandUp = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Up, false);
		moveCommandDown = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Down, false);
		moveCommandLeft = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Left, false);
		moveCommandRight = std::make_shared<GameCommands::DiggerMovement>(m_pPlayerTwo, m_Right, false);
	}


	controllerButton = dae::Controller::ControllerButton::DpadUp;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandUp);
	controllerButton = dae::Controller::ControllerButton::DpadDown;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandDown);
	controllerButton = dae::Controller::ControllerButton::DpadLeft;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandLeft);
	controllerButton = dae::Controller::ControllerButton::DpadRight;
	dae::InputManager::GetInstance().BindControllerToCommand(controller1Index, controllerButton, moveCommandRight);

	const auto& pHealth = std::make_shared<dae::HealthComponent>(m_pPlayerTwo.get(), 4);
	m_pPlayerTwo->AddComponent(pHealth);

	const auto& pPoints = std::make_shared<dae::PointsComponent>(m_pPlayerTwo.get(), 0);
	m_pPlayerTwo->AddComponent(pPoints);

	//HealthCommand* dieCommand = new HealthCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_O, dieCommand);
	//PointCommand* pointCommand = new PointCommand{ GameObjBomberman.get() };
	//dae::InputManager::GetInstance().BindKeyToCommand(SDL_SCANCODE_P, pointCommand);



	//Lives Display
	const auto& PlayerTwoLives = std::make_shared<dae::GameObject>("Player_02");
	//const auto& fontUI = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	//const auto& textBomberManLives = std::make_shared<dae::UIComponent>(fontUI, "Lives: ",
	//	"Lives", PlayerTwoLives.get());
	PlayerTwoLives->SetRelativePosition({ 5, 400 });
	//PlayerTwoLives->AddComponent(textBomberManLives);
	//background->AddChild(PlayerTwoLives);
	scene.Add(PlayerTwoLives);

	//Points Display
	const auto& PlayerTwoPoints = std::make_shared<dae::GameObject>("Player_02");
	//const auto& textBluePoints = std::make_shared<dae::UIComponent>(fontUI, "Points: ",
	//	"Points", PlayerTwoPoints.get());
	PlayerTwoPoints->SetRelativePosition({ 5, 420 });	
	//PlayerTwoPoints->AddComponent(textBluePoints);
	//background->AddChild(PlayerTwoPoints);
	scene.Add(PlayerTwoPoints);


	scene.Add(m_pPlayerTwo);
}
