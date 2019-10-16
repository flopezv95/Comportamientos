#include "../../stdafx.h"
#include "GameLostScene.h"
#include "../Entity/Entity2.h"
#include "../Component/Transform.h"
#include "../Component/Animator.h"
#include "SceneManager.h"
#include "../Component/Text.h"
#include "../Component/Button.h"
#include "../Component/Velocity.h"
#include "../Component/AIController.h"

extern float g_widthScreen;
extern float g_heightScreen;
extern CSceneManager * g_pSM;
//*******************************************************************************
//
//*******************************************************************************
CGameLostScene::CGameLostScene() : CGameBaseScene2(CGameBaseScene2::ELostGameScene)
{
	//Add the background
	m_pBackGround = nullptr;
	//Add the title
	m_pText = nullptr;
}
//*******************************************************************************
//
//*******************************************************************************
CGameLostScene::~CGameLostScene()
{
	RemoveEntity(m_pBackGround);
	DEL(m_pBackGround);
	RemoveEntity(m_pText);
	DEL(m_pText);
	RemoveEntity(m_pButton);
	DEL(m_pButton);
}
//**************************************************************************************************************
//
//**************************************************************************************************************
int CGameLostScene::Init()
{
	//Add the background
	m_pBackGround = NEW(CEntity2, ("BackGround"));
	m_pBackGround->SetPosition(400.0f, 300.0f);
	m_pBackGround->AddComponent(NEW(CAnimator, (m_pBackGround, "data/images/forest.png")));
	m_pBackGround->AddComponent(NEW(CVelocity, (m_pBackGround)));
	AddEntity(m_pBackGround);
	//Add the title
	m_pText = NEW(CEntity2, ("Title"));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("THE BEE'S GAME"), 300.0, 550.0)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("SCORE"), 20.0, 15.0)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("GAME OVER"), g_widthScreen / 2 - 80, g_heightScreen / 2 - 150)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("For play again push 'R'"), g_widthScreen / 4 + 10 , g_heightScreen / 2 - 120)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("For exit the game push 'Esc'"), g_widthScreen / 4 - 20, g_heightScreen / 2 - 90)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("0"), 50.0, 35.0)));
	AddEntity(m_pText);

	//Add button
	m_pButton = NEW(CEntity2, ("Button"));
	auto callback = [](CButton * pButton)
	{
		g_pSM->SetScene(CGameBaseScene2::EPlayGameScene);
	};
	m_pButton->AddComponent(NEW(CButton, (m_pButton, callback, 'R')));
	AddEntity(m_pButton);

	return 0;
}