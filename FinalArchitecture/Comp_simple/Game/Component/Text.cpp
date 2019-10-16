#include "../../stdafx.h"
#include "Text.h"
#include "../ManageMessages/Message.h"
#include "../../include\font.h"
#include "../Entity/Entity2.h"

extern CGraphics * g_pGR2;
//****************************************************************************************
//
//****************************************************************************************
CText::CText(CEntity2 * pEntity, const String & filename, const String & textToWrite, double x, double y): CComponent2 (EText,pEntity)
{
	m_pText = NEW(Font, (filename));
	m_pText->Render(textToWrite, x, y);
	m_string = textToWrite;
	m_pmyText= NEW (Text,());
	m_pmyText->myFont = m_pText;
	m_pmyText->textToWrite = textToWrite;
	m_pmyText->xPosition = x;
	m_pmyText->yPosition = y;
	g_pGR2->AddText(m_pmyText);
}
//****************************************************************************************
//
//****************************************************************************************
CText::~CText()
{
	g_pGR2->RemoveText(m_pmyText);
	m_pText = nullptr;
}
//****************************************************************************************
//
//****************************************************************************************
void CText::Update(float fDelta)
{
	TMessageGetCollision * pMessage = new TMessageGetCollision;
	GetEntity()->ManageMessage(pMessage);
	int fruitCollision;
	pMessage->GetNumberOfCollisionWithFruit(fruitCollision);
	if (fruitCollision > 0)
	{
		char buf[16]; // need a buffer for that
		sprintf(buf, "%d", fruitCollision);
		const char* p = buf;
		m_pmyText->textToWrite = p;
	}
}
