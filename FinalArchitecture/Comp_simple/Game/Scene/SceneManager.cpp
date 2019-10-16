#include "../../stdafx.h"
#include "SceneManager.h"
#include "GameSceneMainMenu2.h"
#include "GamePlayScene.h"
#include "GameLostScene.h"
//****************************************************************************************************************
//
//****************************************************************************************************************
CSceneManager::CSceneManager()
{
	m_pCurrentScene = NULL;
	m_nPendingScene = CGameBaseScene2::EInvalid;
	SetSceneInternal(CGameBaseScene2::EMainMenuScene);
}
//****************************************************************************************************************
//
//****************************************************************************************************************
CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pCurrentScene);
}
//****************************************************************************************************************
//
//****************************************************************************************************************
void CSceneManager::Update(float fDelta)
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update(fDelta);
	if (m_nPendingScene != CGameBaseScene2::EInvalid)
	{
		SetSceneInternal(m_nPendingScene);
		m_nPendingScene = CGameBaseScene2::EInvalid;
	}
}
//****************************************************************************************************************
//
//****************************************************************************************************************
int CSceneManager::SetScene(CGameBaseScene2::TScene sceneToPut)
{
	m_nPendingScene = sceneToPut;
	return RET_OK;
}
//****************************************************************************************************************
//
//****************************************************************************************************************
void CSceneManager::SetSceneInternal(CGameBaseScene2::TScene scene)
{
	if (!m_pCurrentScene || (m_pCurrentScene->GetType() != scene))
	{
		SAFE_DELETE(m_pCurrentScene);
		switch (scene)
		{
		case CGameBaseScene2::EMainMenuScene:
			m_pCurrentScene = NEW(CGameSceneMainMenu2, ());
			break;
		case CGameBaseScene2::EPlayGameScene:
			m_pCurrentScene = NEW(CGamePlayScene, ());
			break;
		case CGameBaseScene2::ELostGameScene:
			m_pCurrentScene = NEW(CGameLostScene, ());
			break;
		}
		if (m_pCurrentScene)
			m_pCurrentScene->Init();
	}
}
