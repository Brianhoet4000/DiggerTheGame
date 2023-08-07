#include "Bullet.h"

#include "BulletComponent.h"
#include "GameCollisionComponent.h"
#include "TextureComponent.h"

dae::Bullet::Bullet(glm::vec2 pos, glm::vec2 vel)
	:m_Vel{ vel }
{
	m_pBullet = std::make_shared<dae::GameObject>("Bullet");

	//Texture
	auto pBulletTexture = std::make_shared<dae::TextureComponent>(m_pBullet.get());
	pBulletTexture->SetTexture("Sprites/Bullet.png");
	m_pBullet->AddComponent(pBulletTexture);

	//Collision
	auto pBulletCollider = std::make_shared<dae::GameCollisionComponent>(m_pBullet.get());
	pBulletCollider->SetRenderCollisionBox(true);
	pBulletCollider->SetCollisionRectOffset(6);
	m_pBullet->AddComponent(pBulletCollider);

	//BulletComponent
	auto pBulletComponent = std::make_shared<dae::BulletComponent>(m_pBullet.get(), m_Vel);
	m_pBullet->AddComponent(pBulletComponent);

	//Pos
	m_pBullet->SetRelativePosition({ pos });
}
