#include "../../stdafx.h"
#include "../Entity/Entity2.h"
#include "GameOverController.h"
#include "Component2.h"
#include "../Scene/SceneManager.h"
#include "../InputManager/InputManager2.h"

extern CSceneManager * g_pSM;
//****************************************************************************************
//
//****************************************************************************************
CGameOverController::CGameOverController(CEntity2 * pEntity, CEntity2 * pLifeImage1, CEntity2 * pLifeImage2, CEntity2 * pLifeImage3) : CComponent2 (EGameOver, pEntity)
{
	m_pLife1 = pLifeImage1;
	m_pLife2 = pLifeImage2;
	m_pLife3 = pLifeImage3;
}
//****************************************************************************************
//
//****************************************************************************************
CGameOverController::~CGameOverController()
{
	m_pLife1 = nullptr;
	m_pLife2 = nullptr;
	m_pLife3 = nullptr;
}
//****************************************************************************************
//
//****************************************************************************************
void CGameOverController::Update(float fDelta)
{
	TMessageGetCollision * pMessage = new TMessageGetCollision;
	GetEntity()->ManageMessage(pMessage);
	int rockCollision;
	pMessage->GetNumberOfCollisionWithRock(rockCollision);
	if (rockCollision == 1)
	{
		m_pLife1->RemoveComponents();
	}
	else if (rockCollision == 2)
	{
		m_pLife2->RemoveComponents();
	}
	else if (rockCollision == 3)
	{
		m_pLife3->RemoveComponents();
		g_pSM->SetScene(CGameBaseScene2::ELostGameScene);
	}
}
