#include "../../../stdafx.h"
#include "GameSprite.h"
#include "../../../include/Image.h"
#include "../../../include/Sprite.h"
#include "../../../include/Screen.h"


// ****************************************************************************
//
// ****************************************************************************
CGameSprite::CGameSprite(const char *psz_image_file)
{
	m_pImage	= new Image	(psz_image_file);
	m_pSprite	= new Sprite(m_pImage);

	m_pSprite->SetPosition(0.0f, 0.0f, 0.0f);
	m_pSprite->SetScale(1.0f, 1.0f);
	m_pSprite->SetAngle(0.0f);
	m_pSprite->Update(0);
}
// ****************************************************************************
//
// ****************************************************************************
void CGameSprite::SetPosition(float x, float y, float z)
{
	m_pSprite->SetPosition(x - (m_pImage->GetWidth()) / 2, y - (m_pImage->GetHeight() / 2), z);
}
// ****************************************************************************
//
// ****************************************************************************
void CGameSprite::SetScale(float sx, float sy)
{
	m_pSprite->SetScale(sx, sy);
}
// ****************************************************************************
//
// ****************************************************************************
void CGameSprite::SetRotation(float r)
{
	m_pSprite->SetAngle(r);
}
// ****************************************************************************
//
// ****************************************************************************
CGameSprite::~CGameSprite()
{
}