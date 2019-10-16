#ifndef __MESSAGE__
#define __MESSAGE__

/*
Para comunicar los componenetes entre si sse utiliza un sistema por mensajes,
el cual comunica siempre el mensaje de un evento y el componenete interesado 
lo recibe y hace lo que sea pertinenete con la informacion que le llega
*/

#include "../../include\sprite.h"
#include "../Entity/Entity2.h"

class CEntity2;

class TMessage
{
public:

	enum TType
	{
		EGetTransform,
		EGetVelocity,
		EGetSprite,
		EGetCollision,
	};

	TMessage(TType type) { m_type = type; }

	TType GetType() const { return m_type; }
private:
	TType m_type;
};
//********************************************************************************
//
//********************************************************************************
class TMessageGetTransform : public TMessage
{
public:
	TMessageGetTransform():TMessage (EGetTransform){}
	
	void SetTransform (float positionX, float positionY,float scaleX,float scaleY, float rotation)
	{
		m_fPositionX = positionX;
		m_fPositionY = positionY;
		m_fScaleX = scaleX;
		m_fScaleY = scaleY;
		m_fRotation = rotation;
	}

	void GetTransform(float &positionX, float &positionY, float &scaleX, float &scaleY, float &rotation)
	{
		positionX = m_fPositionX;
		positionY = m_fPositionY;
		scaleX = m_fScaleX;
		scaleY = m_fScaleY;
		rotation = m_fRotation;
	}

private:
	float m_fPositionX;
	float m_fPositionY;
	float m_fScaleX;
	float m_fScaleY;
	float m_fRotation;
};
//********************************************************************************
//
//********************************************************************************
class TMessageGetVelocity : public TMessage
{
public:
	TMessageGetVelocity() :TMessage(EGetVelocity) {}

	void SetVelocity(float velocityX, float velocityY)
	{
		m_fVelocityX = velocityX;
		m_fVelocityY = velocityY;
	}

	void GetVelocity(float &velocityX, float &velocityY)
	{
		velocityX = m_fVelocityX;
		velocityY = m_fVelocityY;
	}

private:
	float m_fVelocityX;
	float m_fVelocityY;
};
//********************************************************************************
//
//********************************************************************************
class TMessageGetSprite : public TMessage
{
public:
	TMessageGetSprite() :TMessage(EGetSprite) {}

	void SetSprite(Sprite* Sprite)
	{
		m_pSprite = Sprite;
	}

	void GetSprite(Sprite* &Sprite)
	{
		Sprite = m_pSprite;
	}

private:
	Sprite * m_pSprite;
};
//********************************************************************************
//
//********************************************************************************
class TMessageGetCollision : public TMessage
{
public:
	TMessageGetCollision() :TMessage(EGetCollision) {}

	void SetNumberOfCollisionWithRock(int numCollisionRock)//CEntity2 *pEntity)
	{
		m_iNumberOfCollisionRock = numCollisionRock;
	}

	void GetNumberOfCollisionWithRock(int &numCollisionRock)//CEntity2 * &pEntity)
	{
		numCollisionRock = m_iNumberOfCollisionRock;
	}

	void SetNumberOfCollisionWithFruit(int numCollisionFruit)//CEntity2 *pEntity)
	{
		m_iNumberOfCollisionFruit = numCollisionFruit;
	}

	void GetNumberOfCollisionWithFruit(int &numCollisionFruit)//CEntity2 * &pEntity)
	{
		numCollisionFruit = m_iNumberOfCollisionFruit;
	}

private:
	int m_iNumberOfCollisionRock;
	int m_iNumberOfCollisionFruit;
};



#endif