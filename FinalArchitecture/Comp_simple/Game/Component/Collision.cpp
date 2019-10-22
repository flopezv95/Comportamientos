#include "../../stdafx.h"
#include "../ManageMessages/Message.h"
#include "../collider/graphics/GameSprite.h"
#include "../collider/graphics/Graphics.h"
#include "Collision.h"
#include "../Entity/Entity2.h"
#include "../../include\image.h"
#include "../../include\sprite.h"
#include <string.h>

extern CGraphics * g_pGR2;
extern CCollideManagerSimple * g_pCM;
//****************************************************************************************************
//
//****************************************************************************************************
CCollision::CCollision(CEntity2 * pEntity) :CComponent2(ECollision, pEntity)
{
	TMessageGetSprite * pMessage = new TMessageGetSprite;
	GetEntity()->ManageMessage(pMessage);
	m_collisionInfo = NEW(CCollideManagerSimple::TCollderInfo, ());
	m_collisionInfo->pEntity = pEntity;
	m_collisionInfo->pListener = this;
	pMessage->GetSprite(m_collisionInfo->pSprite);
	g_pCM->AddCollider(m_collisionInfo);
	m_iCollisionWithRock = 0;
	m_iCollisionWithFruits = 0;
}
//****************************************************************************************
//
//****************************************************************************************
CCollision::~CCollision()
{
	g_pCM->RemoveCollider(m_collisionInfo);
	SAFE_DELETE(m_collisionInfo);
}
//****************************************************************************************
//
//****************************************************************************************
void CCollision::CollideWith(CEntity2 *pEntity1, CEntity2 *pEntity2)
{
	std::string str1("Fruit");
	std::string str2("Rock");
	std::string str3("Bee");
	std::string str4("Frontier");
	std::string str5("Bullet");
	if (((str1.compare(pEntity1->GetName()->ToCString())) == 0) && ((str3.compare(pEntity2->GetName()->ToCString())) == 0))
	{
		pEntity1->RemoveComponents();
		m_iCollisionWithFruits++;
	}
	if((((str2.compare(pEntity1->GetName()->ToCString())) == 0) || ((str5.compare(pEntity1->GetName()->ToCString())) == 0)) && ((str3.compare(pEntity2->GetName()->ToCString())) == 0))
	{
		pEntity1->RemoveComponents();
		m_iCollisionWithRock++;
	}
	if (((str1.compare(pEntity1->GetName()->ToCString())) == 0) && ((str4.compare(pEntity2->GetName()->ToCString())) == 0))
	{
		pEntity1->RemoveComponents();
		m_iCollisionWithFruits--;
	}
	if (((str2.compare(pEntity1->GetName()->ToCString())) == 0) && ((str4.compare(pEntity2->GetName()->ToCString())) == 0))
	{
		pEntity1->RemoveComponents();
	}
}
//****************************************************************************************
//
//****************************************************************************************
void CCollision::Update(float fDelta)
{
	g_pCM->CheckCollisions();
}
//****************************************************************************************
//
//****************************************************************************************
void CCollision::ManageMessage(TMessage * pMessage)
{
	switch (pMessage->GetType())
	{
		case TMessage::EGetCollision:
		{
			TMessageGetCollision*p = static_cast<TMessageGetCollision *> (pMessage);
			p->SetNumberOfCollisionWithRock(m_iCollisionWithRock);
			p->SetNumberOfCollisionWithFruit(m_iCollisionWithFruits);
		}
		break;
	}
}