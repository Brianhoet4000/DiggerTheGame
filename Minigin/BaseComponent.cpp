#include "BaseComponent.h"
#include"GameObject.h"

namespace dae
{

	BaseComponent::BaseComponent()
		:m_needsUpdate{ true }
	{
	}

	BaseComponent::~BaseComponent()
	{
	}

	void BaseComponent::Update(float)
	{
	}

	void BaseComponent::FixedUpdate(float)
	{
	}

	void BaseComponent::Render() const
	{

	}
}