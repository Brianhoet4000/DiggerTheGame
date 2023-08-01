#include "RotationComponent.h"

#include <iostream>

#include "GameObject.h"

dae::RotationComponent::RotationComponent(GameObject* owner, float offset, float rotationSpeed)
	:m_Radius(offset)
	,m_RotationSpeed(rotationSpeed)
	,m_OffsetOfTheParent(owner->GetWorldPosition())
{
	m_pOwner = owner;
}

void dae::RotationComponent::Update(float deltaTime)
{
	m_Angle += m_RotationSpeed * deltaTime;
	
	float posX = m_OffsetOfTheParent.x + m_Radius * cosf(m_Angle);
	float posY = m_OffsetOfTheParent.y + m_Radius * sinf(m_Angle);
	m_pOwner->SetRelativePosition(glm::vec2{ posX, posY });

}


