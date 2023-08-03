#include "GameCollisionMngr.h"
#include "GameObject.h"
#include "GoldState.h"

namespace dae
{
    class GoldState;

    void dae::GameCollisionMngr::AddCollisionBox(dae::GameObject* owner, GameCollisionComponent* box)
    {
        m_pOwners.push_back(owner);
        m_pCollisonBoxes.push_back(box);
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
        for (size_t i = 0; i < m_pOwners.size(); ++i)
        {
            if (m_pOwners[i] != nullptr)
            {
                if (m_pOwners[i]->GetTag() == "Wall")
                {
                    m_pWallBoxes.push_back(m_pCollisonBoxes[i]);
                }
            }
        }

        std::cout << "Wall: " << m_pWallBoxes.size() << "\n";
        return m_pWallBoxes;
    }

    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllDirtColliders()
    {
        for (size_t i = 0; i < m_pOwners.size(); ++i)
        {
            if (m_pOwners[i]->GetTag() == "Break")
            {
                m_pDirtBoxes.push_back(m_pCollisonBoxes[i]);
            }
        }

        std::cout << "Dirt: " << m_pDirtBoxes.size() << "\n";
        return m_pDirtBoxes;
    }

    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllEmeraldColliders()
    {
        for (size_t i = 0; i < m_pOwners.size(); ++i)
        {
            if (m_pOwners[i]->GetTag() == "Emerald")
            {
                m_pEmeraldBoxes.push_back(m_pCollisonBoxes[i]);
            }
        }

        return m_pEmeraldBoxes;
    }

    std::vector<dae::GameCollisionComponent*> dae::GameCollisionMngr::GetAllGoldColliders()
    {
        for (size_t i = 0; i < m_pOwners.size(); ++i)
        {
            if (m_pOwners[i]->GetTag() == "Gold")
            {
                m_pGoldBoxes.push_back(m_pCollisonBoxes[i]);
            }
        }

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

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForGoldCollisionComponent(const GameCollisionComponent* box)
    {
        if (m_pGoldBoxes.size() <= 0)
        {
            GetAllGoldColliders();
        }

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
        return nullptr;
    }

    dae::GameCollisionComponent* dae::GameCollisionMngr::CheckForDirtCollisionComponent(const GameCollisionComponent* box)
    {
        if (m_pDirtBoxes.size() <= 0)
        {
            GetAllDirtColliders();
        }

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
        return nullptr;
    }

    bool dae::GameCollisionMngr::CheckForOverlapDirt(const dae::GameCollisionComponent* box) const
    {
        for (const auto& Owners : m_pOwners)
        {
            for (const auto& otherbox : m_pCollisonBoxes)
            {
                if (Owners->GetTag() == "Break")
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

    bool dae::GameCollisionMngr::CheckForOverlapBrokenGold(const dae::GameCollisionComponent* box) const
    {
        for (const auto& otherbox : m_pGoldBoxes)
        {
            if (otherbox->GetOwner()->GetComponent<dae::GoldState>()->GetPickupState())
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

    bool dae::GameCollisionMngr::Raycast(glm::vec2 startpos, glm::vec2 direction, dae::GameCollisionComponent* collisionbox, bool checkDirt)
    {
        if (!m_GetAllCollisions)
        {
            GetAllWallColliders();
            GetAllDirtColliders();
            GetAllEmeraldColliders();
            GetAllGoldColliders();
            m_GetAllCollisions = true;
        }

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