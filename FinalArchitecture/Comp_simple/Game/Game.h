#ifndef __GAME__
#define __GAME__

#include "../include/u-gine.h"
#undef APIENTRY
#undef WINGDIAPI
#include <windows.h>
#include "../bass/bass.h"
#undef LoadImage
#include "./collider/graphics/Graphics.h"
#include "./InputManager/InputManager2.h"
#include "./Scene/GameSceneMainMenu2.h"
#include "./Scene/SceneManager.h"
#include "./collider/CollideManagerSimple.h"
#include "./InputManager/Events2.h"

/*
Esta clase es la que clase juego que controla la logica y render del juego.
*/

class CGame
{
public:
	CGame();
	int Init();
	void End();
	void Update();
	void Render();
	Screen * GetScreen() { return m_pScreen; }
	const Renderer * GetRender() { return m_pRenderer; }

private:
	CInputManager2 * m_pInput_manager;
	Screen*	m_pScreen;
	const Renderer*	m_pRenderer;
	LARGE_INTEGER m_iEndTime;
	LARGE_INTEGER m_iStartTime;
	LARGE_INTEGER m_iClockFrequency;
	float m_fDeltaTime;
};

#endif
