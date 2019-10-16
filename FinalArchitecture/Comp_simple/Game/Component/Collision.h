#ifndef __COLLISION__
#define __COLLISION__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"
#include "../collider/CollideManagerSimple.h"

class CEntity2;
class CGameSprite;
class Image;

class CCollision : public CComponent2 , public CCollideManagerSimple::IListener
{
public:
	CCollision(CEntity2 * pEntity);
	~CCollision();
	virtual void CollideWith(CEntity2 *pEntity1, CEntity2 *pEntity2);
	virtual void ManageMessage(TMessage * pmessage);
	virtual void Update(float fDelta);

private:
	CCollideManagerSimple::TCollderInfo * m_collisionInfo;
	int m_iCollisionWithRock;
	int m_iCollisionWithFruits;
};


#endif