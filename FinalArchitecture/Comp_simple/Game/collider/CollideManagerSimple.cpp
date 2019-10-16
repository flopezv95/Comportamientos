#include "../../stdafx.h"
#include "CollideManagerSimple.h"
#include "../../include/sprite.h"
#include <algorithm>


// ********************************************************************************************
//
// ********************************************************************************************
CCollideManagerSimple::CCollideManagerSimple() {}
CCollideManagerSimple::~CCollideManagerSimple() {}
// ********************************************************************************************
//
// ********************************************************************************************
void CCollideManagerSimple::AddCollider(TCollderInfo *pInfo)
{
	pInfo->pSprite->SetCollision(Sprite::COLLISION_CIRCLE);
	m_aCollides.push_back(pInfo);
}
// ********************************************************************************************
//
// ********************************************************************************************
void CCollideManagerSimple::RemoveCollider(TCollderInfo *pInfo)
{
	m_aCollides.erase(std::remove(m_aCollides.begin(), m_aCollides.end(), pInfo), m_aCollides.end());
}
// ********************************************************************************************
//
// ********************************************************************************************
void CCollideManagerSimple::CheckCollisions()
{
	for (unsigned int i = 0; i < m_aCollides.size(); i++)
		for (unsigned j = i + 1; j < m_aCollides.size(); j++)
		{
			if (m_aCollides[i]->pSprite->CheckCollision(m_aCollides[j]->pSprite))
			{
				if (m_aCollides[i]->pListener)
					m_aCollides[i]->pListener->CollideWith(m_aCollides[j]->pEntity,m_aCollides[i]->pEntity);
			}
		}
}