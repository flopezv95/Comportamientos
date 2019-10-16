#include "../stdafx.h"
#include "Game.h"

CGraphics *g_pGR2 = nullptr;
CSceneManager * g_pSM = nullptr;
CCollideManagerSimple * g_pCM = nullptr;
float g_widthScreen = 800;
float g_heightScreen = 600;
int mouseXPosition, mouseYPosition;

//****************************************************************************************************************
//
//****************************************************************************************************************
CGame::CGame()
{
	m_pInput_manager = nullptr;
	m_pRenderer = nullptr;
	m_pScreen = nullptr;
	m_fDeltaTime = 0;
}
//****************************************************************************************************************
//
//****************************************************************************************************************
int CGame::Init()
{
	const Renderer& renderer = Renderer::Instance();
	Screen& screen = Screen::Instance();
	m_pScreen = &screen;
	m_pRenderer = &renderer;
	m_pScreen->Open(g_widthScreen, g_heightScreen, false);
	m_pInput_manager = NEW(CInputManager2, ());
	g_pGR2 = NEW(CGraphics, ());
	g_pSM = NEW(CSceneManager, ());
	g_pCM = NEW(CCollideManagerSimple, ());
	QueryPerformanceCounter(&m_iEndTime);
	return RET_OK;
}
//****************************************************************************************************************
//
//****************************************************************************************************************
void CGame::End()
{
	ResourceManager::Instance().FreeResources();
	SAFE_DELETE(g_pGR2);
	DEL(m_pInput_manager);
	DUMP_LEAKS
}
//****************************************************************************************************************
//
//****************************************************************************************************************
void CGame::Update()
{

	QueryPerformanceFrequency(&m_iClockFrequency);
	QueryPerformanceCounter(&m_iStartTime);
	LARGE_INTEGER delta;
	delta.QuadPart = m_iStartTime.QuadPart - m_iEndTime.QuadPart;
	m_fDeltaTime = (static_cast<float>(delta.QuadPart)) / (static_cast<float>(m_iClockFrequency.QuadPart));
	m_pInput_manager->Update();
	//// Lógica
	//Opcion1
	//float fDelta = static_cast<float>(m_pScreen->ElapsedTime());
	//g_pSM->Update(fDelta);
	//Opcion2
	g_pSM->Update(m_fDeltaTime*60);
	m_iEndTime = m_iStartTime;
	
}
//****************************************************************************************************************
//
//****************************************************************************************************************
void CGame::Render()
{
	m_pRenderer->Clear(0, 0, 0);	// Limpia pantalla
	g_pGR2->render();		// Pintado de lo que la lógica determina.
	m_pScreen->Refresh();			// Volcado de lo pintado en pantalla.
	mouseXPosition = m_pScreen->GetMouseX();
	mouseYPosition = m_pScreen->GetMouseY();
}
