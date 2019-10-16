#ifndef __ANIMATOR__
#define __ANIMATOR__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"

class CEntity2;
class CGameSprite;

class CAnimator : public CComponent2
{
public:
	CAnimator(CEntity2 * pEntity, const char * psz_image_file);
	~CAnimator();
	virtual void ManageMessage(TMessage * pmessage);
	virtual void Update(float fDelta);
private:
	CGameSprite * m_pSprite;
};


#endif

