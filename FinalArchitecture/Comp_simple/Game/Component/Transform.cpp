#include "../../stdafx.h"
#include "Transform.h"
#include "../../Vector2D.h"

//****************************************************************************************
//
//****************************************************************************************
CTransform::CTransform(CEntity2 * pEntity, float positionX, float positionY, float scaleX, float scaleY, float r) :CComponent2(ETransform, pEntity)
{
	m_fPositionX = positionX;
	m_fPositionY = positionY;
	m_fScaleX = scaleX;
	m_fScaleY = scaleX;
	m_fRotation = r;
}
//****************************************************************************************
//
//****************************************************************************************
Vector2D CTransform::GetPosition()
{
	Vector2D position(m_fPositionX, m_fPositionY); 
	return position;
}
//****************************************************************************************
//
//****************************************************************************************
Vector2D CTransform::GetScale()
{
	Vector2D scale(m_fScaleX, m_fScaleY); 
	return scale;
}
//****************************************************************************************
//
//****************************************************************************************
void CTransform::ManageMessage(TMessage * pMessage)
{
	switch (pMessage->GetType())
	{
	    case TMessage::EGetTransform:
		{
			TMessageGetTransform*p = static_cast<TMessageGetTransform *> (pMessage);
			p->SetTransform(m_fPositionX, m_fPositionY,m_fScaleX,m_fScaleY,m_fRotation);
		}
		break;
	}
}


