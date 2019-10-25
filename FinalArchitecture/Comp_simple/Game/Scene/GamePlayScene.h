#ifndef __GAMEPLAYSCENE__
#define __GAMEPLAYSCENE__

/*
En esta escena es donde el usuario va a controlar el personaje para recoger frutas
y sobrevivir la mayor cantidad de tiempo que pueda.
Esta escena se activa cuando el usuario presiona la tecla 'S' en la escena del menu principal.
Ademas a lo largo de esta escena apareceran de manera aleatoria : frutas, piedras y proyectiles.
*/

#include "GameBaseScene2.h"
#include "../InputManager/Events2.h"
#include <string>

class CGamePlayScene : public CGameBaseScene2
{
public:
	CGamePlayScene(int spawnFruitTime = 60, int spawnRockTime = 120, int fireEnemy=100);
	~CGamePlayScene();
	virtual void Update(float FDelta) override;
	virtual int Init() override;
private:
	int m_iSpawnFruitTime;
	int m_iSpawnRocksTime;
	int m_iFireEnemyRate;
	CEntity2 * m_pBackGround;
	CEntity2 * m_pText;
	CEntity2 * m_pImageLife1;
	CEntity2 * m_pImageLife2;
	CEntity2 * m_pImageLife3;
	CEntity2 * m_pBee;
	CEntity2 * m_pFrontier;
	CEntity2 * m_pEnemy;
	CEntity2 * m_sound;
	std::string m_sFruitText;
	std::vector<const char*> m_MySpawnables;
};
#endif

