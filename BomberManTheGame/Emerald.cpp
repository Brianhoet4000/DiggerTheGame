#include "Emerald.h"

#include "CollisionBoxComponent.h"
#include "GameCollisionComponent.h"
#include "TextureComponent.h"

dae::Emerald::Emerald(glm::vec2 pos)
{
	m_pEmerald = std::make_shared<dae::GameObject>("Emerald");

	//Texture
	auto pEmeraldTexture = std::make_shared<dae::TextureComponent>(m_pEmerald.get());
	m_pEmerald->AddComponent(pEmeraldTexture);
	pEmeraldTexture->SetTexture("Sprites/Emerald.png");

	//Collision
	auto pPickUpCollider = std::make_shared<dae::GameCollisionComponent>(m_pEmerald.get());
	pPickUpCollider->SetRenderCollisionBox(false);
	m_pEmerald->AddComponent(pPickUpCollider);

	

	//Pos
	m_pEmerald->SetRelativePosition({ pos });
}
