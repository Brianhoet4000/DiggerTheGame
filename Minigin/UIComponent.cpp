#pragma once
#include "UIComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"

#include <iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include <chrono>

#include "TextComponent.h"

using namespace dae;

UIComponent::UIComponent(std::shared_ptr<Font> font, const std::string& text, const std::string& type, GameObject* owner) :
	m_pTextCp{ std::make_unique<TextComponent>(text, font, owner) },
	m_Type{ type }
{
	m_pOwner = owner;
	SetText(text);
}


void UIComponent::Update(float deltaTime)
{
	m_pTextCp->Update(deltaTime);
}

void UIComponent::Render() const
{
	m_pTextCp->Render();
}
