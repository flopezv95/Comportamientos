#include "../../stdafx.h"
#include "AIController.h"
#include "../ManageMessages/Message.h"
#include "../Entity/Entity2.h"


//****************************************************************************************
//
//****************************************************************************************
CAIController::CAIController(CEntity2 * pEntity, float limitXLeft, float limitXRight, float limitYUp, float limitYDown) :CComponent2(ELimitMovement, pEntity)
{
	m_flimitXL = limitXLeft;
	m_flimitXR = limitXRight;
	m_flimitYD = limitYDown;
	m_flimitYU = limitYUp;
	m_fvelocityX = -2.0f;
	m_fvelocityY = 0;
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
	if (positionX <= m_flimitXL || positionX >= m_flimitXR)
	{
		m_fvelocityX *=-1;
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
		p->SetVelocity(m_fvelocityX, m_fvelocityY);
	}
	break;
	}

}
