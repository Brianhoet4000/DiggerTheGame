#include "CollisionBoxManager.h"

#include "GameObject.h"
#include "../BomberManTheGame/GoldState.h"

namespace dae
{
	class GoldState;
}

void dae::CollisionBoxManager::AddCollisionBox(dae::GameObject* owner, CollisionBoxComponent* box)
{
    m_pOwners.push_back(owner);
	m_pCollisonBoxes.push_back(box);
}

void dae::CollisionBoxManager::RemoveCollisionBox(CollisionBoxComponent* box)
{
	m_pCollisonBoxes.erase(std::remove(m_pCollisonBoxes.begin(), m_pCollisonBoxes.end(), box), m_pCollisonBoxes.end());
}

void dae::CollisionBoxManager::RemoveDirtBox(CollisionBoxComponent* box)
{
    m_pDirtBoxes.erase(std::remove(m_pDirtBoxes.begin(), m_pDirtBoxes.end(), box), m_pDirtBoxes.end());
}

void dae::CollisionBoxManager::RemoveEmeraldBox(CollisionBoxComponent* box)
{
    m_pEmeraldBoxes.erase(std::remove(m_pEmeraldBoxes.begin(), m_pEmeraldBoxes.end(), box), m_pEmeraldBoxes.end());
}

void dae::CollisionBoxManager::RemoveGoldBox(CollisionBoxComponent* box)
{
    m_pGoldBoxes.erase(std::remove(m_pGoldBoxes.begin(), m_pGoldBoxes.end(), box), m_pGoldBoxes.end());
}

std::vector<dae::CollisionBoxComponent*> dae::CollisionBoxManager::GetAllWallColliders()
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

std::vector<dae::CollisionBoxComponent*> dae::CollisionBoxManager::GetAllDirtColliders()
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

std::vector<dae::CollisionBoxComponent*> dae::CollisionBoxManager::GetAllEmeraldColliders()
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

std::vector<dae::CollisionBoxComponent*> dae::CollisionBoxManager::GetAllGoldColliders()
{
    for (size_t i = 0; i < m_pOwners.size(); ++i)
    {
        if (m_pOwners[i]->GetTag() == "Gold")
        {
            m_pEmeraldBoxes.push_back(m_pCollisonBoxes[i]);
        }
    }

    return m_pGoldBoxes;
}

bool dae::CollisionBoxManager::CheckForCollision(const CollisionBoxComponent* box) const
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

dae::CollisionBoxComponent* dae::CollisionBoxManager::CheckForCollisionComponent(const CollisionBoxComponent* box) const
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

bool dae::CollisionBoxManager::CheckForOverlapDirt(const dae::CollisionBoxComponent* box) const
{
    for (const auto& Owners : m_pOwners)
    {
        for (const auto& otherbox : m_pCollisonBoxes)
        {
            if(Owners->GetTag() == "Break")
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

bool dae::CollisionBoxManager::CheckForOverlapBrokenGold(const dae::CollisionBoxComponent* box) const
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

bool dae::CollisionBoxManager::Raycast(glm::vec2 startpos, glm::vec2 direction, dae::CollisionBoxComponent* collisionbox, bool checkDirt)
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
    if(checkDirt)
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
