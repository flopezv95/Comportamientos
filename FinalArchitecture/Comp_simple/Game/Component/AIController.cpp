#include "../../stdafx.h"
#include "AIController.h"
#include "../ManageMessages/Message.h"
#include "../Entity/Entity2.h"


//****************************************************************************************
//
//****************************************************************************************
CAIController::CAIController(CEntity2 * pEntity, float limitXLeft, float limitXRight, float limitYUp, float limitYDown) :CComponent2(ELimitMovement, pEntity)
{
	m_fLimitXL = limitXLeft;
	m_fLimitXR = limitXRight;
	m_fLimitYD = limitYDown;
	m_fLimitYU = limitYUp;
	m_fVelocityX = -2.0f;
	m_fVelocityY = 0;
}
//****************************************************************************************
//
//****************************************************************************************
CAIController::~CAIController()
{
}
//****************************************************************************************
//
//****************************************************************************************
void CAIController::Update(float fDelta)
{
	TMessageGetTransform * pMessage = new TMessageGetTransform;
	GetEntity()->ManageMessage(pMessage);
	float positionX, positionY, scaleX, scaleY, rotation;
	pMessage->GetTransform(positionX, positionY, scaleX, scaleY, rotation);
	if (positionX <= m_fLimitXL || positionX >= m_fLimitXR)
	{
		m_fVelocityX *=-1;
	}
}
// ****************************************************************************
//
// ****************************************************************************
void CAIController::ManageMessage(TMessage * pmessage)
{
	switch (pmessage->GetType())
	{
	case TMessage::EGetVelocity:
	{
		TMessageGetVelocity*p = static_cast<TMessageGetVelocity *> (pmessage);
		p->SetVelocity(m_fVelocityX, m_fVelocityY);
	}
	break;
	}

}
