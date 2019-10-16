#ifndef  __SCENEMANAGER__
#define __SCENEMANAGER__

/*
Esta clase es la que maneja la escena actual y cuando se tiene que cambiar,
es decir controla las diferentes condiciones para mantener la escena o cambiarla
*/

#include "GameBaseScene2.h"

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	void Update(float fDelta);
	int SetScene(CGameBaseScene2::TScene sceneToPut);

private:
	void SetSceneInternal(CGameBaseScene2::TScene scene);
	CGameBaseScene2 * m_pCurrentScene;
	CGameBaseScene2::TScene m_nPendingScene;
};

#endif




