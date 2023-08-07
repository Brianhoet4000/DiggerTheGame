#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#pragma once
#include "Minigin.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Scene.h"
#include <iostream>

#include "GameObject.h"
#include "Commands.h"
#include "GameCollisionMngr.h"
#include "ScreenManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"
#include <Renderer.h>

void load()
{
	std::cout << "--Tab to switch gamemode--\n";
	std::cout << "--E To Accept--\n";
	std::cout << "--F2 To pause and resume music--\n";

	std::cout << "--How To Play--\n";
	std::cout << "WASD to move character\n";
	std::cout << "Space to shoot\n";
	std::cout << "Dpad to move secondPlayer\n";
	std::cout << "A to shoot\n";
	
	auto Screenmanager = std::make_unique<dae::ScreenManager>();
	Screenmanager->CreateMenuScreen();
	//const float scale{ 1.08f };
	//SDL_RenderSetScale(dae::Renderer::GetInstance().GetSDLRenderer(), scale, scale);
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}