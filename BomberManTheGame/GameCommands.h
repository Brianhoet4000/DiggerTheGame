#pragma once
#include "BulletTimerComponent.h"
#include "Commands.h"
#include "GameCollisionComponent.h"
#include "LevelPrefab.h"
#include "ScreenManager.h"

namespace GameCommands
{

	class DiggerMovement : public dae::Command
	{
	private:
		glm::vec2 m_Dir{};
		dae::GameCollisionComponent* m_pCollision;
		bool m_Digger;
		bool m_DoOnce = false;
	public:
		DiggerMovement(dae::GameObject* owner, const glm::vec2& dir, bool digger);
		virtual void Execute(float deltaTime) override;
	};

	class ShootingBullet : public dae::Command
	{
	private:
		glm::vec2 m_Dir{};
		dae::Scene* m_Scene;
		dae::BulletTimerComponent* m_pBulletTimer{};
	public:
		ShootingBullet(dae::GameObject* owner,dae::Scene* scene);
		virtual void Execute(float deltaTime) override;
	};

	class SwitchGameMode : public dae::Command
	{
	private:
		std::shared_ptr<dae::GameObject> m_pScreen{};
		dae::GameObject* m_pTextMode;
		dae::ScreenManager* m_pScreenManager{};
		int m_CurrentScreen;
	public:
		SwitchGameMode(std::shared_ptr<dae::GameObject> owner, dae::GameObject* text, const int& currentScreen, dae::ScreenManager* screen);
		virtual void Execute(float) override;

	};

	class AcceptGameMode : public dae::Command
	{
	private:
		std::shared_ptr<dae::GameObject> m_pScreen{};
		dae::ScreenManager* m_pScreenManager{};
		bool m_Pressed{ false };
	public:
		AcceptGameMode(std::shared_ptr<dae::GameObject> owner, dae::ScreenManager* screen);
		virtual void Execute(float) override;
	};

	class SkipLevel : public dae::Command
	{
	private:
		dae::Scene* m_pScene;
		dae::LevelPrefab* m_pLevel;

	public:
		SkipLevel(dae::GameObject* owner,dae::Scene* scene, dae::LevelPrefab* level);
		virtual void Execute(float) override;
	};

	class MuteMusic : public dae::Command
	{
	private:

	public:
		MuteMusic() = default;
		virtual void Execute(float) override;
	};

}
