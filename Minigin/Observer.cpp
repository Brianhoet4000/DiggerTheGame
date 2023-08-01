#pragma once
#include "Observer.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "Counter.h"
#include "UIComponent.h"

#include <iostream>

void dae::UI::Notify(Event event, dae::GameObject* owner)
{
	switch (event)
	{
	case PLAYER_DIED:
		UpdateUI(owner, "Lives");
		std::cout << "ACTOR DIED - From Observer\n";
		break;
	case SCORE_ADDED:
		UpdateUI(owner, "Points");
		break;
	case Update:
		UpdateUI(owner, "Points");
		UpdateUI(owner, "Lives");
	}
}

void dae::UI::UpdateUI(dae::GameObject* owner, const std::string& UIType)
{
	std::string newValue{};
	dae::UIComponent* text{};

	for (auto sibling : owner->GetParent()->GetChildren())
	{
		if (sibling->ReturnDeleting()) continue;

		if (sibling->GetTag() != owner->GetTag())
			continue;


		if (auto textCp = sibling->GetComponent<dae::UIComponent>())
		{
			if (textCp->GetType() == UIType)
				text = textCp;
		}

		if (UIType == "Lives")
		{
			if (auto hp = sibling->GetComponent<dae::HealthComponent>())
			{
				newValue = std::to_string(hp->GetAmount());
			}

		}
		else if (UIType == "Points")
		{
			if (auto points = sibling->GetComponent<dae::PointsComponent>())
			{
				newValue = std::to_string(points->GetAmount());
				std::cout << points->GetAmount() << '\n';
			}
		}

	}

	if (text)
	{
		text->SetText(text->GetBeginText() + newValue);
	}

}
