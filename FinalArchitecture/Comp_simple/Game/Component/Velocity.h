#ifndef __VELOCITY__
#define __VELOCITY__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"
class CEntity2;

class CVelocity : public CComponent2
{
public:
	CVelocity(CEntity2 * pEntity = nullptr, float velocityX=0.0f, float velocityY=0.0f);
	virtual void Update(float fDelta) {} 
	virtual void ManageMessage(TMessage * pmessage);
private:
	float m_fVelocityX;
	float m_fVelocityY;
};

#endif


