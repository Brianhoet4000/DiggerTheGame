#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void RemoveScene(std::shared_ptr<dae::Scene> scene);
		void NextScene();
		void SetActiveScene(const std::string& sceneName);
		std::shared_ptr<Scene> GetActiveScene() const { return m_pScenes[m_ActiveScene]; }
		std::string GetActiveSceneName() const;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_pScenes;

		int m_ActiveScene{ 0 };
	};
}
