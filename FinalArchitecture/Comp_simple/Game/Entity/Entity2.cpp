#include "../../stdafx.h"
#include "Entity2.h"
#include "../Component/Transform.h"
#include "../Component/Component2.h"
#include "../../Vector2D.h"

//****************************************************************************************
//
//****************************************************************************************
CEntity2::CEntity2(const char * name)
{
	m_pName =NEW(String,(name));
	m_pTransform = NEW(CTransform,(this, 0.0f, 0.0f));
	this->AddComponent(m_pTransform);
}
//*******************************************************************************
//
//*******************************************************************************
CEntity2::~CEntity2()
{
	RemoveComponents();
}
//*******************************************************************************
//
//*******************************************************************************
void CEntity2::Update(float fDelta)
{
	for (CComponent2 *p : m_components)
		p->Update(fDelta);
}
//*******************************************************************************
//
//*******************************************************************************
void CEntity2::ManageMessage(TMessage * pmessage)
{
	for (CComponent2 *p : m_components)
		p->ManageMessage(pmessage);
}
//*******************************************************************************
//
//*******************************************************************************
void CEntity2::AddComponent(CComponent2 * p)
{
	m_components.push_back(p);
}
void CEntity2::RemoveComponents()
{
	for (CComponent2 *p : m_components)
	{
		SAFE_DELETE(p);
	}
	m_components.clear();
}
//*******************************************************************************
//
//*******************************************************************************
void CEntity2::SetPosition(float fPositionX, float fPositionY)
{
	m_pTransform->SetPosition(fPositionX, fPositionY);
}
//*******************************************************************************
//
//*******************************************************************************
void CEntity2::SetScale(float fScaleX, float fScaleY)
{
	m_pTransform->SetScale(fScaleX, fScaleY);
}
//*******************************************************************************
//
//*******************************************************************************
Vector2D  CEntity2::GetPosition()
{
	Vector2D positionToReturn(m_pTransform->GetPosition().getX(), m_pTransform->GetPosition().getY());
	return positionToReturn;
}
//*******************************************************************************
//
//*******************************************************************************
Vector2D  CEntity2::GetScale()
{
	Vector2D scaleToReturn(m_pTransform->GetScale().getX(), m_pTransform->GetScale().getY());
	return scaleToReturn;
}
