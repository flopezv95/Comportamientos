#include "../../stdafx.h"
#include "Button.h"
#include "Component2.h"
#include "../InputManager/InputManager2.h"
#include "../InputManager/Events2.h"


extern CInputManager2 * g_pIM;
//****************************************************************************************
//
//****************************************************************************************
CButton::CButton(CEntity2 * pEntity, std::function<void(CButton*)> callback, char key) :CComponent2(EButton, pEntity)
{
	g_pIM->RegisterToEvent(this);
	m_callback = callback;
	m_ckey = key;
}

CButton::CButton(CEntity2 * pEntity, std::function<void(CButton*)> callback, bool bUseLeftButton, int higherLimitX, int lowerLimitX, int higherLimitY, int lowerLimitY) :CComponent2(EButton, pEntity)
{
	g_pIM->RegisterToEvent(this);
	m_callback = callback;
	m_bUseLeftButton = bUseLeftButton;
	m_iHigherLimitX = higherLimitX;
	m_iLowerLimitX = lowerLimitX;
	m_iHigherLimitY = higherLimitY;
	m_iLowerLimitY = lowerLimitY;
}
//****************************************************************************************
//
//****************************************************************************************
CButton::~CButton()
{
	g_pIM->DeregisterToEvent(this);
}
//****************************************************************************************
//
//****************************************************************************************
void CButton::ManageEvent(TEvent * pEvent)
{
	if (pEvent->GetType() == TEvent::EKeyboardDown)
	{
		TEventKeyboardDown *p = static_cast<TEventKeyboardDown *> (pEvent);
		if (p->Getkey() == m_ckey)
		{
			m_callback(this);
		}
	}
	else if (pEvent->GetType() == TEvent::EMouseDownLeft)
	{
		if (m_bUseLeftButton)
		{
			TEventMouseDownLeft *p = static_cast<TEventMouseDownLeft *> (pEvent);
			if (p->Getx() > m_iLowerLimitX && p->Getx() < m_iHigherLimitX && p->Gety() > m_iLowerLimitY && p->Gety() < m_iHigherLimitY)
			{
				m_callback(this);
			}
		}
	}
}
