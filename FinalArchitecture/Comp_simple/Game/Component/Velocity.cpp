#include "../../stdafx.h"
#include "Velocity.h"

//****************************************************************************************
//
//****************************************************************************************
CVelocity::CVelocity(CEntity2 * pEntity, float velocityX, float velocityY) :CComponent2(EVelocity, pEntity)
{
	m_fVelocityX = velocityX;
	m_fVelocityY = velocityY;
}
//****************************************************************************************
//
//****************************************************************************************
void CVelocity::ManageMessage(TMessage * pmessage)
{
	switch (pmessage->GetType())
	{
	case TMessage::EGetVelocity:
	{
		TMessageGetVelocity*p = static_cast<TMessageGetVelocity *> (pmessage);
		p->SetVelocity(m_fVelocityX,m_fVelocityY);
	}
	break;
	}
	
}
