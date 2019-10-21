#ifndef __TRANSFORM__
#define __TRANSFORM__

/*
Se creo una Arquitectura basada en componenetes para tener entidades mas independientes,
y que estas entidades esten definidas por los componenetes que tengan y puedan ser lo flexibles
que el programador quiera. Es decir, cada entidad puede tener cualquier componente
*/

#include "Component2.h"

extern int mouseXPosition, mouseYPosition;

class CEntity2;
class Vector2D;

class CTransform : public CComponent2
{
public:
	CTransform(CEntity2 * pEntity = nullptr, float positionX = 0, float positionY = 0, float scaleX = 1.0f, float scaleY = 1.0f, float r = 0.0f);
	void SetPosition(float x, float y) { m_fPositionX = x; m_fPositionY = y; }
	void SetScale(float x, float y) { m_fScaleX = x; m_fScaleY = y; }
	Vector2D GetPosition();
	Vector2D GetScale();
	virtual void Update(float fDelta) {} 
	virtual void ManageMessage(TMessage * pmessage);

private:
	float m_fPositionX;
	float m_fPositionY;
	float m_fScaleX;
	float m_fScaleY;
	float m_fRotation;
};


#endif

