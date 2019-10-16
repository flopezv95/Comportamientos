#include "../../stdafx.h"
#include "Animator.h"
#include "../ManageMessages/Message.h"
#include "../collider/graphics/GameSprite.h"
#include "../collider/graphics/Graphics.h"
#include "../Entity/Entity2.h"

extern CGraphics * g_pGR2;
//****************************************************************************************
//
//****************************************************************************************
CAnimator::CAnimator(CEntity2 * pEntity, const char * psz_image_file) :CComponent2(EAnimator, pEntity)
{
	m_pSprite = g_pGR2->AddSprite(psz_image_file);
	m_pSprite->SetPosition(0.0f, 0.0f, 0.0f);
}
//****************************************************************************************
//
//****************************************************************************************
CAnimator::~CAnimator()
{
	g_pGR2->RemoveSprite(m_pSprite);
	m_pSprite = nullptr;
}
//****************************************************************************************
//
//****************************************************************************************
void CAnimator::Update(float fDelta)
{
	
	TMessageGetTransform * pMessage = new TMessageGetTransform;
	GetEntity()->ManageMessage(pMessage);
	float positionX, positionY, scaleX, scaleY, rotation;
	pMessage->GetTransform(positionX, positionY, scaleX, scaleY, rotation);
	TMessageGetVelocity * pMessage2 = new TMessageGetVelocity;
	GetEntity()->ManageMessage(pMessage2);
	float velocityX, velocityY;
	pMessage2->GetVelocity(velocityX, velocityY);
	GetEntity()->SetPosition((positionX)+(velocityX*fDelta), (positionY)+(velocityY*fDelta));
	m_pSprite->SetPosition((positionX)+(velocityX*fDelta), (positionY)+(velocityY*fDelta), 0.0f);
	m_pSprite->SetScale(scaleX, scaleY);
	m_pSprite->SetRotation(rotation);
	
}
//****************************************************************************************
//
//****************************************************************************************
void CAnimator::ManageMessage(TMessage * pMessage)
{
	switch (pMessage->GetType())
	{
	case TMessage::EGetSprite:
	{
		TMessageGetSprite*p = static_cast<TMessageGetSprite *> (pMessage);
		p->SetSprite(m_pSprite->GetEngineSprite());
	}
	break;
	}
}

