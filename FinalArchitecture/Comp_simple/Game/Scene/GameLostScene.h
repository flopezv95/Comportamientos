#ifndef __GAMELOSTCENE__
#define __GAMELOSTSCENE__

/*
Esta escena contiene el texto para indicarle al jugador que perdio y que debe presionar para 
volver a jugar si este lo desea.
Esta escena se activa solo si el jugador perdio todas las vidas
*/

#include "GameBaseScene2.h"
#include "../InputManager/Events2.h"
#include <string>

class CGameLostScene : public CGameBaseScene2
{
public:
	CGameLostScene();
	~CGameLostScene();
	virtual int Init() override;
private:
	
	CEntity2 * m_pBackGround;
	CEntity2 * m_pText;
	CEntity2 * m_pButton;
};
#endif
