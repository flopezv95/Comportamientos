#ifndef  __GAMEOVER__
#define __GAMEOVER__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"

class CEntity2;

class CGameOverController : public CComponent2
{
public:
	CGameOverController(CEntity2 * pEntity, CEntity2 * pLifeImage1, CEntity2 * pLifeImage2, CEntity2 * pLifeImage3);

	~CGameOverController();

	virtual void Update(float fDelta);

private:
	CEntity2 * m_pLife1;
	CEntity2 * m_pLife2;
	CEntity2 * m_pLife3;
};

#endif

