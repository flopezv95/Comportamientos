#ifndef  __AICONTROLLER__
#define __AICONTROLLER__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles 
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"

class CEntity2;

class CAIController : public CComponent2
{
public:
	CAIController(CEntity2 * pEntity, float limitXLeft = 0, float limitXRight = 0, float limitYUp = 0, float limitYDown = 0);

	~CAIController();

	virtual void Update(float fDelta);

	virtual void ManageMessage(TMessage * pmessage);

private:
	float m_fLimitXL;
	float m_fLimitXR;
	float m_fLimitYU;
	float m_fLimitYD;
	float m_fVelocityX;
	float m_fVelocityY;
};

#endif
