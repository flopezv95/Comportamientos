#ifndef __GAMESCENEMAINMENU__
#define __GAMESCENEMAINMENU__
#include "GameBaseScene2.h"

/*
Esta escena es la primera que el usuario ve al iniciar el juego.
En esta escena esta las instrucciones para iniciar el juego
*/

class CEntity2;

class CGameSceneMainMenu2 : public CGameBaseScene2
{

public:

	CGameSceneMainMenu2();
	~CGameSceneMainMenu2();

	virtual int Init() override;

private:
	CEntity2 * m_pBackGround;
	CEntity2 * m_pText;
	CEntity2 * m_pImageLife1;
	CEntity2 * m_pImageLife2;
	CEntity2 * m_pImageLife3;
	CEntity2 * m_pButton;
};

#endif