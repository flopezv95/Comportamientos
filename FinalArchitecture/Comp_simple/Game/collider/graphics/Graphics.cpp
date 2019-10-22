#include "../../../stdafx.h"
#include "Graphics.h"
#include "GameSprite.h"
#include "../../Component/Text.h"
#include "../../../include/Scene.h"
#include "../../../include/font.h"
// ****************************************************************************
//
// ****************************************************************************
CGraphics::CGraphics()
{
	m_pScene = NEW(Scene, ());
}
// ****************************************************************************
//
// ****************************************************************************
CGraphics::~CGraphics()
{
	SAFE_DELETE(m_pScene);
}
// ****************************************************************************
//
// ****************************************************************************
void CGraphics::render()
{
	if (m_pScene)
		m_pScene->Render();
	for (Text *p : m_myFonts)
		p->myFont->Render(p->textToWrite,p->xPosition,p->yPosition);

}
// ****************************************************************************
//
// ****************************************************************************
CGameSprite *CGraphics::AddSprite(const char *psz_file)
{
	CGameSprite *pSprite = NEW(CGameSprite, (psz_file));
	m_pScene->AddSprite(pSprite->GetEngineSprite(), Scene::LAYER_FRONT);
	return pSprite;
}
// ****************************************************************************
//
// ****************************************************************************
void CGraphics::RemoveSprite(CGameSprite *pSprite)
{
	m_pScene->RemoveSprite(pSprite->GetEngineSprite(), Scene::LAYER_FRONT);
	SAFE_DELETE(pSprite);
}
// ****************************************************************************
//
// ****************************************************************************
void CGraphics::AddText(Text * myFont)
{
	m_myFonts.push_back(myFont);
}
// ****************************************************************************
//
// ****************************************************************************
void CGraphics::RemoveText(Text* myFont)
{
	std::vector<Text*>::iterator it = std::find(m_myFonts.begin(), m_myFonts.end(), myFont);
	if (it != m_myFonts.end())
	{
		DEL(*it);
		m_myFonts.erase(it);
	}
}
// ****************************************************************************
//
// ****************************************************************************
float CGraphics::GetWidth()	{ return Screen::Instance().GetWidth();	}
float CGraphics::GetHeight()	{ return Screen::Instance().GetHeight(); }
