#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GoldState.h"

namespace dae
{
    class GoldState;

    void dae::GameCollisionMngr::AddCollisionBox(dae::GameObject* owner, GameCollisionComponent* box)
    {
        m_pCollisonBoxes.push_back(box);

        //Check which tag
        {
            if (owner->GetTag() == "Gold")
            {
                m_pGoldBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Emerald")
            {
                m_pEmeraldBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Break")
            {
                m_pDirtBoxes.push_back(box);
            }
            else if (owner->GetTag() == "Wall")
            {
                m_pWallBoxes.push_back(box);
            }
        }
    }

    void dae::GameCollisionMngr::RemoveCollisionBox(GameCollisionComponent* box)
    {
        m_pCollisonBoxes.erase(std::remove(m_pCollisonBoxes.begin(), m_pCollisonBoxes.end(), box), m_pCollisonBoxes.end());
    }
    void dae::GameCollisionMngr::RemoveDirtBox(GameCollisionComponent* box)
    {
        m_pDirtBoxes.erase(std::remove(m_pDirtBoxes.begin(), m_pDirtBoxes.end(), box), m_pDirtBoxes.end());
    }
    void dae::GameCollisionMngr::RemoveEmeraldBox(GameCollisionComponent* box)
    {
        m_pEmeraldBoxes.erase(std::remove(m_pEmeraldBoxes.begin(), m_pEmeraldBoxes.end(), box), m_pEmeraldBoxes.end());
    }
    void dae::GameCollisionMngr::RemoveGoldBox(GameCollisionComponent* box)
    {
        m_pGoldBoxes.erase(std::remove(m_pGoldBoxes.begin(), m_pGoldBoxes.end(), box), m_pGoldBoxes.end());
    }

    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllWallColliders()
    {
        std::cout << "Wall: " << m_pWallBoxes.size() << "\n";
        return m_pWallBoxes;
    }
    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllDirtColliders()
    {
        std::cout << "Dirt: " << m_pDirtBoxes.size() << "\n";
        return m_pDirtBoxes;
    }
    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllEmeraldColliders()
    {
        std::cout << "Emerald: " << m_pEmeraldBoxes.size() << "\n";
        return m_pEmeraldBoxes;
    }
    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllGoldColliders()
    {
        std::cout << "Gold: " << m_pGoldBoxes.size() << "\n";
        return m_pGoldBoxes;
    }

    bool dae::GameCollisionMngr::CheckForCollision(const GameCollisionComponent* box) const
    {
        for (const auto& otherBox : m_pCollisonBoxes)
        {
            if (otherBox == box)
                continue;

            if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
            {
                return true;
            }
        }

        return false;


    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForCollisionComponent(const GameCollisionComponent* box) const
    {
        for (const auto& otherBox : m_pCollisonBoxes)
        {
            if (otherBox == box)
                continue;

            if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
            {
                return otherBox;
            }
        }
        return nullptr;
    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForGoldCollisionComponent(const GameCollisionComponent* box) const
    {
        if (!m_pGoldBoxes.empty())
        {
            for (const auto& otherBox : m_pGoldBoxes)
            {
                if (otherBox == box)
                    continue;

                if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
                {
                    return otherBox;
                }
            }
        }
        return nullptr;
    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForDirtCollisionComponent(const GameCollisionComponent* box) const
    {
        if (!m_pDirtBoxes.empty())
        {
            for (const auto& otherBox : m_pDirtBoxes)
            {
                if (otherBox == box)
                    continue;

                if (box->GetCollisionRect().x < otherBox->GetCollisionRect().x + otherBox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherBox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherBox->GetCollisionRect().y + otherBox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherBox->GetCollisionRect().y)
                {
                    return otherBox;
                }
            }
        }
        return nullptr;
    }

    bool dae::GameCollisionMngr::CheckForOverlapDirt(const dae::GameCollisionComponent* box) const
    {
        if (!m_pDirtBoxes.empty())
        {
            for (const auto& otherbox : m_pDirtBoxes)
            {
                if (box->GetCollisionRect().x < otherbox->GetCollisionRect().x + otherbox->GetCollisionRect().w &&
                    box->GetCollisionRect().x + box->GetCollisionRect().w > otherbox->GetCollisionRect().x &&
                    box->GetCollisionRect().y < otherbox->GetCollisionRect().y + otherbox->GetCollisionRect().h &&
                    box->GetCollisionRect().y + box->GetCollisionRect().h > otherbox->GetCollisionRect().y)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool dae::GameCollisionMngr::CheckForOverlapBrokenGold(const dae::GameCollisionComponent* box) const
    {
        if (!m_pGoldBoxes.empty())
        {
            for (const auto& otherbox : m_pGoldBoxes)
            {
                if (otherbox->GetOwner()->GetComponent<dae::GoldState>()->GetCoinsBool())
                {
                    if (box->GetCollisionRect().x < otherbox->GetCollisionRect().x + otherbox->GetCollisionRect().w &&
                        box->GetCollisionRect().x + box->GetCollisionRect().w > otherbox->GetCollisionRect().x &&
                        box->GetCollisionRect().y < otherbox->GetCollisionRect().y + otherbox->GetCollisionRect().h &&
                        box->GetCollisionRect().y + box->GetCollisionRect().h > otherbox->GetCollisionRect().y)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void GameCollisionMngr::PlayerLogicBox(dae::GameCollisionComponent* ownerBox, glm::vec2 dir)
    {
        auto OverlappedBox = CheckForCollisionComponent(ownerBox);

        if (OverlappedBox != nullptr)
        {
            //Dirt block delete
            if (OverlappedBox->GetOwner()->GetTag() == "Break")
            {
                dae::GameCollisionMngr::GetInstance().RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                dae::GameCollisionMngr::GetInstance().RemoveDirtBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
            }

            //Overlap with emerald pick up
            if (OverlappedBox->GetOwner()->GetTag() == "Emerald")
            {
                RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                RemoveEmeraldBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                OverlappedBox->GetOwner()->MarkTrueForDeleting();
                
            }

            //Gold Related
            if (OverlappedBox->GetOwner()->GetTag() == "Gold")
            {
                auto goldState = OverlappedBox->GetOwner()->GetComponent<dae::GoldState>();

                //If Gold not Broken and falls die
                if(!goldState->GetCoinsBool() && goldState->GetMoneyBagState() == dae::GoldState::Falling)
                {
                    ownerBox->GetOwner()->MarkTrueForDeleting();
                    RemoveCollisionBox(ownerBox);
                }

                //Push Gold Left
                if (goldState->GetMoneyBagState() != dae::GoldState::Falling
                    && dir.x > 0)
                {
                    glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x + m_Dim, OverlappedBox->GetOwner()->GetRelativePosition().y };
                    OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                    
                }
                //Push Gold Right
                else if (goldState->GetMoneyBagState() != dae::GoldState::Falling
                    && dir.x < 0)
                {
                    glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x - m_Dim * 2, OverlappedBox->GetOwner()->GetRelativePosition().y };
                    OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                }

                //If Gold Broken and overlap pick up
                if (goldState->GetCoinsBool())
                {
                    RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    RemoveGoldBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    OverlappedBox->GetOwner()->MarkTrueForDeleting();
                }
            }
        }
    }

    void GameCollisionMngr::NobbinLogicBox(dae::GameCollisionComponent* ownerBox, glm::vec2 dir)
    {
        auto OverlappedBox = CheckForGoldCollisionComponent(ownerBox);
        auto OtherOverLappedBox = CheckForDirtCollisionComponent(ownerBox);
        //Gold Nobbin
        if(OverlappedBox != nullptr)
        {
            if(OverlappedBox->GetOwner()->GetTag() == "Gold")
            {
                auto goldState = OverlappedBox->GetOwner()->GetComponent<dae::GoldState>();

                if(OtherOverLappedBox != nullptr)
                {
                    //If Gold not Broken and falls die
                    if (!goldState->GetCoinsBool() && goldState->GetMoneyBagState() == dae::GoldState::Falling)
                    {
                        ownerBox->GetOwner()->MarkTrueForDeleting();
                        RemoveCollisionBox(ownerBox);
                    }

                    if(OtherOverLappedBox->GetOwner()->GetTag() == "Break")
                    {
                        //Push Gold Left
                        if(goldState->GetMoneyBagState() != dae::GoldState::Falling && dir.x > 0)
                        {
                            OtherOverLappedBox->GetOwner()->MarkTrueForDeleting();
                            RemoveDirtBox(OtherOverLappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());

                            glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x + m_Dim, OverlappedBox->GetOwner()->GetRelativePosition().y };
                            OverlappedBox->GetOwner()->SetRelativePosition(newPos);

                        }
                        //Push Gold Right
                        else if(goldState->GetMoneyBagState() != dae::GoldState::Falling && dir.x < 0)
                        {
                            OtherOverLappedBox->GetOwner()->MarkTrueForDeleting();
                            RemoveDirtBox(OtherOverLappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());

                            glm::vec2 newPos = { OverlappedBox->GetOwner()->GetRelativePosition().x - m_Dim, OverlappedBox->GetOwner()->GetRelativePosition().y };
                            OverlappedBox->GetOwner()->SetRelativePosition(newPos);
                        }
                    }
                }

                //If Gold Broken and overlap pick up
                if (goldState->GetCoinsBool())
                {
                    RemoveCollisionBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    RemoveGoldBox(OverlappedBox->GetOwner()->GetComponent<dae::GameCollisionComponent>());
                    OverlappedBox->GetOwner()->MarkTrueForDeleting();
                }
            }
        }
    }

    bool dae::GameCollisionMngr::Raycast(glm::vec2 startpos, glm::vec2 direction,const dae::GameCollisionComponent* collisionbox, bool checkDirt) const
    {
        /*
        std::cout << "Wall: " << m_pWallBoxes.size() << '\n';
        std::cout << "Dirt: " << m_pDirtBoxes.size() << '\n';
        std::cout << "Emerald: " << m_pEmeraldBoxes.size() << '\n';
        std::cout << "Gold: " << m_pGoldBoxes.size() << '\n';
        */

        glm::vec2 startPos = startpos;
        startPos.x += collisionbox->GetCollisionRect().w / 2.0f;
        startPos.y += collisionbox->GetCollisionRect().h / 2.0f;

        glm::vec2 dir = glm::normalize(direction);
        float distance = collisionbox->GetCollisionRect().w / 2.f;
        const float offset{ 1.f };
        // Check for collision with obstacles
        for (const auto& boxes : m_pWallBoxes)
        {

            if (startPos.x + (dir.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
                startPos.x + dir.x * distance - offset >= boxes->GetCollisionRect().x &&
                startPos.y + (dir.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
                startPos.y + dir.y * distance - offset >= boxes->GetCollisionRect().y)
            {
                return false;
            }

        }
        if (checkDirt)
        {
            for (const auto& boxes : m_pDirtBoxes)
            {

                if (startPos.x + (dir.x * distance + offset) <= boxes->GetCollisionRect().x + boxes->GetCollisionRect().w &&
                    startPos.x + dir.x * distance - offset >= boxes->GetCollisionRect().x &&
                    startPos.y + (dir.y * distance + offset) <= boxes->GetCollisionRect().y + boxes->GetCollisionRect().h &&
                    startPos.y + dir.y * distance - offset >= boxes->GetCollisionRect().y)
                {
                    return false;
                }
            }
        }
        return true;
    }

}