#include "BulletComponent.h"

#include <memory>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "TextureComponent.h"


dae::BulletComponent::BulletComponent(dae::GameObject* owner, glm::vec2 vel)
	:m_vel{vel}
{
	m_pOwner = owner;

	m_pBullet = std::make_shared<dae::GameObject>();
	m_pBullet->SetRelativePosition(glm::vec2{-10, -10});
	auto textureBullet = std::make_shared<dae::TextureComponent>(m_pBullet.get());
	textureBullet->SetTexture("Sprites/Bullet.png");
	m_pBullet->AddComponent(textureBullet);
}

void dae::BulletComponent::Update(float deltaTime)
{
	const auto newPos = m_pBullet->GetRelativePosition() + m_vel * deltaTime;
	m_pBullet->SetRelativePosition(newPos);
}
