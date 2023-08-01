#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float deltaTime)
{
	for(const auto& scene : m_pScenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::FixedUpdate(float deltaTime)
{
	for (const auto& scene : m_pScenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_pScenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::RemoveScene(std::shared_ptr<dae::Scene> scene)
{
	m_pScenes.erase(std::remove(m_pScenes.begin(), m_pScenes.end(), scene), m_pScenes.end());
}

void dae::SceneManager::NextScene()
{
	m_pScenes[m_ActiveScene]->SetActive(false);

	++m_ActiveScene;
	if (m_ActiveScene >= static_cast<int>(m_pScenes.size()))
		m_ActiveScene = 0;

	m_pScenes[m_ActiveScene]->SetActive(true);
}

void dae::SceneManager::SetActiveScene(const std::string& sceneName)
{
	m_pScenes[m_ActiveScene]->SetActive(false);

	for (int i{}; i < static_cast<int>(m_pScenes.size()); ++i)
	{
		if (m_pScenes[i]->GetName() != sceneName) continue;

		m_ActiveScene = i;
		m_pScenes[m_ActiveScene]->SetActive(true);
	}
}

std::string dae::SceneManager::GetActiveSceneName() const
{
	return m_pScenes[m_ActiveScene]->GetName();
}
