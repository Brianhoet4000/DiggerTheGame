#include "GameCollisionComponent.h"

#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "Renderer.h"
#include "TextureComponent.h"

dae::GameCollisionComponent::GameCollisionComponent(dae::GameObject* owner, bool IsVersus)
	:m_IsVersus{ IsVersus }
{
	m_pOwner = owner;
	m_CollisionBox.w = m_pOwner->GetComponent<dae::TextureComponent>()->GetSize().x;
	m_CollisionBox.h = m_pOwner->GetComponent<dae::TextureComponent>()->GetSize().y;

	GameCollisionMngr::GetInstance().AddCollisionBox(m_pOwner, this);
}

void dae::GameCollisionComponent::Update(float)
{
	m_CollisionBox.x = m_pOwner->GetWorldPosition().x + m_Offset;
	m_CollisionBox.y = m_pOwner->GetWorldPosition().y + m_Offset;
}

void dae::GameCollisionComponent::Render() const
{
	if (m_RenderCollisionBox)
	{
		//
		// Color red { 255,0,0,1 };
	//SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer() ,&m_CollisionBox);
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 0, 255, 0, 1);
		SDL_RenderDrawRectF(Renderer::GetInstance().GetSDLRenderer(), &m_CollisionBox);
	}
}

SDL_FRect dae::GameCollisionComponent::GetCollisionRect() const
{
	return m_CollisionBox;
}

void dae::GameCollisionComponent::SetCollisionRectOffset(float Offset)
{
	m_Offset = Offset;
	m_CollisionBox.w = m_pOwner->GetComponent<dae::TextureComponent>()->GetSize().x - (Offset * 2.0f);
	m_CollisionBox.h = m_pOwner->GetComponent<dae::TextureComponent>()->GetSize().y - (Offset * 2.0f);
}

dae::GameObject* dae::GameCollisionComponent::GetOwner() const
{
	return m_pOwner;
}
