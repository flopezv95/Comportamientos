#include "../../stdafx.h"
#include "../Entity/Entity2.h"
#include "GameBaseScene2.h"


CGameBaseScene2::CGameBaseScene2(TScene type)
{
	m_myScene = type;
}
//*******************************************************************************
//
//*******************************************************************************
CGameBaseScene2::~CGameBaseScene2()
{
	for (auto pEntity : m_entities)
	{
		DEL(pEntity);
	}
	m_entities.clear();
}
//*******************************************************************************
//
//*******************************************************************************
void CGameBaseScene2::Update(float fDelta)
{
	for (CEntity2 *p : m_entities)
		p->Update(fDelta);
}
//********************************************************************************
//
//********************************************************************************
int CGameBaseScene2::Init()
{
	return 0;
}
//*******************************************************************************
//
//*******************************************************************************
CGameBaseScene2::TScene CGameBaseScene2::GetType()
{
	return m_myScene;
}
//*******************************************************************************
//
//*******************************************************************************
void CGameBaseScene2::AddEntity(CEntity2 * p)
{
	m_entities.push_back(p);
}
//*******************************************************************************
//
//*******************************************************************************
void CGameBaseScene2::RemoveEntity(CEntity2 * p)
{

	std::vector<CEntity2*>::iterator it = std::find(m_entities.begin(), m_entities.end(), p);
	if (it != m_entities.end())
	{
		DEL(*it);
		m_entities.erase(it);
	}
}
