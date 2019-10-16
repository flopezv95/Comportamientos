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
}
