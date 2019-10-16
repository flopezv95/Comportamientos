#ifndef __COLLIDEMANAGERSIMPLE___
#define __COLLIDEMANAGERSIMPLE___

#include <vector>
/*
Ademas, se creo una serie que maneje todo lo que es collisiones entre entidades,
esto nos da un manejo independiente de las collisiones que utilizan el Ilistener
para saber cuando collisionaron con otra entidad
*/
class CEntity2;
class Sprite;

class CCollideManagerSimple
{
public:

	class IListener
	{
	public:
		virtual void CollideWith(CEntity2 *pEntity1, CEntity2 *pEntity2) = 0;
	};

	struct TCollderInfo
	{
		IListener	*	pListener;
		CEntity2	*		pEntity;
		Sprite *		pSprite;
		TCollderInfo() { pListener = 0; pEntity = 0; pSprite = 0; }
	};


	virtual void AddCollider	(TCollderInfo *pInfo);
	virtual void RemoveCollider(TCollderInfo *pInfo);

	virtual void CheckCollisions();

	CCollideManagerSimple();
	~CCollideManagerSimple();

private:
	std::vector<TCollderInfo *>m_aCollides;
};

#endif
