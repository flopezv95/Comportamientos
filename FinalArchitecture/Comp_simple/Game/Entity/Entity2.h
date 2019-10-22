#ifndef  __ENTITY2__
#define __ENTITY2__
#include <vector>
/*
Gracias a que la arquitectura que se eligio fue una arquitectura basada en componenetes, 
se necesitaba crear una clase para las entidades que estuviera vacia, y que solo
tuviera una transformada en el mundo.

Ademas las entidades estan compuestas de componenetes, asi que cada entidad esta definida por
los componenetes que la conformen, se pueden agregar y eliminar de la entidad
*/

class TMessage;
class CTransform;
class String;
class Vector2D;
class CComponent2;

class CEntity2
{

public:
	CEntity2(const char * name);
	~CEntity2();
	void Update(float fDelta);
	void ManageMessage(TMessage * pmessage);

	void AddComponent(CComponent2 * p);

	void RemoveComponents();

	void SetPosition(float fPositionX, float fPositionY);
	void SetScale(float fScaleX, float fScaleY);
	Vector2D  GetPosition();
	Vector2D  GetScale();
	String*  GetName() { return m_pName; }


private:
	std::vector<CComponent2*> m_components;
	CTransform* m_pTransform;
	String* m_pName;
};


#endif


