#include "../../stdafx.h"
#include "GameSceneMainMenu2.h"
#include "../Entity/Entity2.h"
#include "../Component/Transform.h"
#include "../Component/Animator.h"
#include "SceneManager.h"
#include "../Component/Text.h"
#include "../Component/Button.h"
#include "../Component/Velocity.h"

extern CSceneManager * g_pSM;
//***************************************************************************************************
//
//***************************************************************************************************
CGameSceneMainMenu2::CGameSceneMainMenu2() : CGameBaseScene2(CGameBaseScene2::EMainMenuScene)
{
	//Add the background
	m_pBackGround = nullptr;
	//Add the title
	m_pText = nullptr;
	//Add life images
	m_pImageLife1 = nullptr;
	m_pImageLife2 = nullptr;
	m_pImageLife3 = nullptr;
	//Add button
	m_pButton = nullptr;
}
//***************************************************************************************************
//
//***************************************************************************************************
CGameSceneMainMenu2::~CGameSceneMainMenu2()
{
	RemoveEntity(m_pBackGround);
	SAFE_DELETE(m_pBackGround);
	RemoveEntity(m_pText);
	SAFE_DELETE(m_pText);
	RemoveEntity(m_pImageLife1);
	SAFE_DELETE(m_pImageLife1);
	RemoveEntity(m_pImageLife2);
	SAFE_DELETE(m_pImageLife2);
	RemoveEntity(m_pImageLife3);
	SAFE_DELETE(m_pImageLife3);
	RemoveEntity(m_pButton);
	SAFE_DELETE(m_pButton);
}
//****************************************************************************************
//
//****************************************************************************************
int CGameSceneMainMenu2::Init()
{
	//Add the background
	m_pBackGround = NEW(CEntity2, ("BackGround"));
	m_pBackGround->SetPosition(400.0f, 300.0f);
	m_pBackGround->AddComponent(NEW(CAnimator, (m_pBackGround, "data/images/forest.png")));
	m_pBackGround->AddComponent(NEW(CVelocity, (m_pBackGround)));
	AddEntity(m_pBackGround);
	//Add text
	m_pText = NEW(CEntity2, ("Text"));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("THE BEE'S GAME"), 300.0, 550.0)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("SCORE"), 20.0, 15.0)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("0"), 50.0, 35.0)));
	m_pText->AddComponent(NEW(CText, (m_pText, String("data/fonts/font.png"), String("PRESS TO START THE GAME"), 220.0, 150.0)));
	AddEntity(m_pText);
	//Add life images
	m_pImageLife1 = NEW(CEntity2, ("LifeImage"));
	m_pImageLife1->SetPosition(680.0f, 45.0f);
	m_pImageLife1->SetScale(0.6f, 0.6f);
	m_pImageLife1->AddComponent(NEW(CAnimator, (m_pImageLife1, "data/images/bee_life.png")));
	m_pImageLife1->AddComponent(NEW(CVelocity, (m_pImageLife1)));
	AddEntity(m_pImageLife1);
	m_pImageLife2 = NEW(CEntity2, ("LifeImage"));
	m_pImageLife2->SetPosition(730.0f, 45.0f);
	m_pImageLife2->SetScale(0.6f, 0.6f);
	m_pImageLife2->AddComponent(NEW(CAnimator, (m_pImageLife2, "data/images/bee_life.png")));
	m_pImageLife2->AddComponent(NEW(CVelocity, (m_pImageLife2)));
	AddEntity(m_pImageLife2);
	m_pImageLife3 = NEW(CEntity2, ("LifeImage"));
	m_pImageLife3->SetPosition(780.0f, 45.0f);
	m_pImageLife3->SetScale(0.6f, 0.6f);
	m_pImageLife3->AddComponent(NEW(CAnimator, (m_pImageLife3, "data/images/bee_life.png")));
	m_pImageLife3->AddComponent(NEW(CVelocity, (m_pImageLife3)));
	AddEntity(m_pImageLife3);
	//Add button
	m_pButton = NEW(CEntity2, ("Button"));
	m_pButton->SetPosition(585.0f, 280.0f);
	m_pButton->SetScale(0.3f, 0.3f);
	m_pButton->AddComponent(NEW(CAnimator, (m_pButton, "data/images/start.jpg")));
	m_pButton->AddComponent(NEW(CVelocity, (m_pButton)));
	auto callback = [](CButton * pButton)
	{
		g_pSM->SetScene(CGameBaseScene2::EPlayGameScene);
	};
	m_pButton->AddComponent(NEW(CButton, (m_pButton, callback,true)));
	AddEntity(m_pButton);
	return 0;
}

