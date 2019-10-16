#include "../../stdafx.h"
#include "InputManager2.h"
#include"Events2.h"
#include "../../lib/glfw.h"

CInputManager2 * g_pIM = nullptr;
//*****************************************************************************************
//
//*****************************************************************************************
void callback_mouse_button2(int ibutton, int iAction)
{
	g_pIM->injectMouseEvent(ibutton, iAction);
}
//*****************************************************************************************
//
//*****************************************************************************************
void callback_key2(int ikey , int iAction)
{
	g_pIM->injectKeyboardEvent(ikey, iAction);
}
void callback_mouse_position(double xpos, double ypos) { //Funcion callback para guardar la posicion del cursor


}
//*****************************************************************************************
//CInputManager2
//*****************************************************************************************
CInputManager2::CInputManager2()
{
	g_pIM = this;
	glfwSetMouseButtonCallback(callback_mouse_button2);
	glfwSetKeyCallback(callback_key2);
}

CInputManager2::~CInputManager2()
{
	for (TEvent* event : m_events)
	{
		DEL(event);
	}
}
//*****************************************************************************************
//
//*****************************************************************************************
void CInputManager2::DeregisterToEvent(IListener * pObserver)
{
	
		for (int i =0; i< m_listeners.size(); i++)
		{
			if (m_listeners[i] == pObserver)
			{
				m_listeners.erase(m_listeners.begin()+i);
			}

		}
			
}
//*****************************************************************************************
//
//*****************************************************************************************
void CInputManager2::RegisterToEvent(CInputManager2::IListener * pObserver)
{
	m_listeners.push_back(pObserver);
}
//*****************************************************************************************
//
//*****************************************************************************************
void CInputManager2::injectMouseEvent(int ibutton, int iAction)
{
	if (ibutton==GLFW_MOUSE_BUTTON_1 && iAction==GLFW_RELEASE)
	{
		int x, y;
		glfwGetMousePos(&x, &y);
		TEvent *pEvent = NEW(TEventMouseDownLeft, (x,y));
		m_events.push_back(pEvent);
	}
}
//*****************************************************************************************
//
//*****************************************************************************************
void CInputManager2::injectKeyboardEvent(int ikey, int iAction)
{
	if (iAction)
	{
		TEvent *pEvent = NEW(TEventKeyboardDown, (static_cast<unsigned int>(ikey)));
		m_events.push_back(pEvent);
	}
}
//*****************************************************************************************
//
//*****************************************************************************************
void CInputManager2::Update()
{
	glfwPollEvents();
	for (TEvent* event : m_events)
	{
		int size = m_listeners.size();
		for (IListener* listener : m_listeners)
			listener->ManageEvent(event);
		DEL(event);
	}
	m_events.clear();
}