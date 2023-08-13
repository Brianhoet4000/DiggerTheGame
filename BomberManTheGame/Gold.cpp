#include "Gold.h"

//#include "CountDownTimer.h"
#include "GameCollisionComponent.h"
#include "GoldStateComponent.h"
#include "TextureComponent.h"

dae::Gold::Gold(glm::vec2 pos)
{
	m_pGold = std::make_shared<dae::GameObject>("Gold");

	//Texture
	auto pTexture = std::make_shared<TextureComponent>(m_pGold.get());
	m_pGold->AddComponent(pTexture);
	pTexture->SetTexture("Sprites/GoldBag.png");

	//Collision
	auto pCollider = std::make_shared<GameCollisionComponent>(m_pGold.get());
	pCollider->SetRenderCollisionBox(true);
	m_pGold->AddComponent(pCollider);

	//auto pTimer = std::make_shared<dae::CountDownTimer>(m_pGold.get(), 3.f);
	//m_pGold->AddComponent(pTimer);

	//GoldLogic
	auto pGoldStateCp = std::make_shared<GoldStateComponent>(m_pGold.get());
	m_pGold->AddComponent(pGoldStateCp);

	//Pos
	m_pGold->SetRelativePosition({ pos });
}
