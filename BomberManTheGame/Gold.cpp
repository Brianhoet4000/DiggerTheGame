#include "Gold.h"

#include "CollisionBoxComponent.h"
#include "CountDownTimer.h"
#include "GoldState.h"
#include "TextureComponent.h"

dae::Gold::Gold(dae::GameObject* , glm::vec2 pos)
{
	m_pGold = std::make_shared<dae::GameObject>("Gold");

	//Texture
	auto pEmeraldTexture = std::make_shared<dae::TextureComponent>(m_pGold.get());
	m_pGold->AddComponent(pEmeraldTexture);
	pEmeraldTexture->SetTexture("Sprites/GoldBag.png");

	//Collision
	auto pPickUpCollider = std::make_shared<dae::CollisionBoxComponent>(m_pGold.get());
	pPickUpCollider->SetRenderCollisionBox(true);
	m_pGold->AddComponent(pPickUpCollider);

	auto pTimer = std::make_shared<dae::CountDownTimer>(m_pGold.get(), 3.f);
	m_pGold->AddComponent(pTimer);

	//GoldLogic
	auto pGoldStateCp = std::make_shared<dae::GoldState>(m_pGold.get());
	m_pGold->AddComponent(pGoldStateCp);

	//Pos
	m_pGold->SetRelativePosition({ pos });
}
