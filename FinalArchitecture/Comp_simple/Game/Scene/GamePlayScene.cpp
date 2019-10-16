#include "../../stdafx.h"
#include "GamePlayScene.h"
#include "../Entity/Entity2.h"
#include "../Component/Transform.h"
#include "../Component/Animator.h"
#include "SceneManager.h"
#include "../Component/Text.h"
#include "../Component/Button.h"
#include "../Component/Velocity.h"
#include "../Component/Collision.h"
#include "../Component/GameOverController.h"
#include "../../Vector2D.h"
#include "../Component/AIController.h"

extern int mouseXPosition, mouseYPosition;
extern float g_widthScreen;
extern float g_heightScreen;
//**************************************************************************************************************
//
//**************************************************************************************************************
CGamePlayScene::CGamePlayScene(int spawnFruitTime, int spawnRockTime, int fireEnemy) : CGameBaseScene2(CGameBaseScene2::EPlayGameScene)
{
	m_iSpawnFruitTime = spawnFruitTime;
	m_iSpawnRocksTime = spawnRockTime;
	m_iFireEnemyRate = fireEnemy;
	//Add the background
	m_pBackGround      = nullptr;
	//Add the title
	m_pText          = nullptr;
	//Add life images
	m_pImageLife1      = nullptr;
	m_pImageLife2      = nullptr;
	m_pImageLife3      = nullptr;
	m_pBee             = nullptr;
	str1 = "Fruit";
	//Add Enemy
	m_pEnemy = nullptr;
	//Add frontier
	m_pFrontier = nullptr;
	//Add fruits
	m_MySpawnables.push_back("data/images/eyecandy_1.png");
	m_MySpawnables.push_back("data/images/eyecandy_2.png");
	m_MySpawnables.push_back("data/images/eyecandy_3.png");
	m_MySpawnables.push_back("data/images/eyecandy_4.png");
	m_MySpawnables.push_back("data/images/Stone3.png");

}
//**************************************************************************************************************
//
//**************************************************************************************************************
CGamePlayScene::~CGamePlayScene()
{
	RemoveEntity(m_pBackGround);
	DEL(m_pBackGround);
	RemoveEntity(m_pText);
	DEL(m_pText);
	RemoveEntity(m_pBee);
	DEL(m_pBee);
	RemoveEntity(m_pEnemy);
	DEL(m_pEnemy);
	RemoveEntity(m_pFrontier);
	DEL(m_pFrontier);
}
//**************************************************************************************************************
//
//**************************************************************************************************************
void CGamePlayScene::Update(float FDelta)
{
	CGameBaseScene2::Update(FDelta);
	m_pBee->SetPosition(mouseXPosition, mouseYPosition);
	if (rand() % m_iSpawnFruitTime == 0) { //Ver cuando el numero rando es igual a cero

		CEntity2 * fruit = NEW(CEntity2, ("Fruit"));
		fruit->SetPosition(rand() % 800, 0.0f);
		fruit->AddComponent(NEW(CAnimator, (fruit, m_MySpawnables[rand() % 4])));
		fruit->AddComponent(NEW(CVelocity, (fruit, 0.0f, rand() % 1 + 3)));
		fruit->AddComponent (NEW(CCollision, (fruit)));
		AddEntity(fruit);
	}
	if (rand() % m_iSpawnRocksTime == 0) { //Ver cuando el numero rando es igual a cero

		CEntity2 * rock = NEW(CEntity2, ("Rock"));
		rock->SetPosition(rand() % 800, 0.0f);
		rock->SetScale(0.5f, 0.5f);
		rock->AddComponent(NEW(CAnimator, (rock, m_MySpawnables[4])));
		rock->AddComponent(NEW(CVelocity, (rock, 0.0f, rand() % 1 + 4)));
		rock->AddComponent(NEW(CCollision, (rock)));
		AddEntity(rock);
	}
	if (rand() % m_iFireEnemyRate == 0) { //Ver cuando el numero rando es igual a cero

		CEntity2 * bullet = NEW(CEntity2, ("Bullet"));
		bullet->SetPosition(m_pEnemy->GetPosition()->getX()-150.0f, m_pEnemy->GetPosition()->getY()-100.f);
		bullet->SetScale(0.35f, 0.35f);
		bullet->AddComponent(NEW(CAnimator, (bullet, "data/images/Projectile.png")));
		bullet->AddComponent(NEW(CVelocity, (bullet, 0.0f, ((rand() % 2 + 5)*-1))));
		bullet->AddComponent(NEW(CCollision, (bullet)));
		AddEntity(bullet);
	}
	

}
//**************************************************************************************************************
//
//**************************************************************************************************************
int CGamePlayScene::Init()
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
	AddEntity(m_pText);
	//Add Frontier
	m_pFrontier = NEW(CEntity2, ("Frontier"));
	m_pFrontier->SetPosition(2300.0f, 1750.0f);
	m_pFrontier->SetScale(1.0f, 1.0f);
	m_pFrontier->AddComponent(NEW(CAnimator, (m_pFrontier, "data/images/end.png")));
	m_pFrontier->AddComponent(NEW(CVelocity, (m_pFrontier)));
	m_pFrontier->AddComponent(NEW(CCollision, (m_pFrontier)));
	AddEntity(m_pFrontier);
	//Add life images
	m_pImageLife1 = NEW(CEntity2, ("LifeImage1"));
	m_pImageLife1->SetPosition(680.0f, 45.0f);
	m_pImageLife1->SetScale(0.6f, 0.6f);
	m_pImageLife1->AddComponent(NEW(CAnimator, (m_pImageLife1, "data/images/bee_life.png")));
	m_pImageLife1->AddComponent(NEW(CVelocity, (m_pImageLife1)));
	AddEntity(m_pImageLife1);
	m_pImageLife2 = NEW(CEntity2, ("LifeImage2"));
	m_pImageLife2->SetPosition(730.0f, 45.0f);
	m_pImageLife2->SetScale(0.6f, 0.6f);
	m_pImageLife2->AddComponent(NEW(CAnimator, (m_pImageLife2, "data/images/bee_life.png")));
	m_pImageLife2->AddComponent(NEW(CVelocity, (m_pImageLife2)));
	AddEntity(m_pImageLife2);
	m_pImageLife3 = NEW(CEntity2, ("LifeImage3"));
	m_pImageLife3->SetPosition(780.0f, 45.0f);
	m_pImageLife3->SetScale(0.6f, 0.6f);
	m_pImageLife3->AddComponent(NEW(CAnimator, (m_pImageLife3, "data/images/bee_life.png")));
	m_pImageLife3->AddComponent(NEW(CVelocity, (m_pImageLife3)));
	AddEntity(m_pImageLife3);
	//Add Bee
	m_pBee = NEW(CEntity2, ("Bee"));
	m_pBee->SetPosition(mouseXPosition, mouseYPosition);
	m_pBee->AddComponent(NEW(CAnimator,  (m_pBee, "data/images/bee_life.png")));
	m_pBee->AddComponent(NEW(CVelocity,  (m_pBee)));
	m_pBee->AddComponent(NEW(CCollision, (m_pBee)));
	m_pBee->AddComponent(NEW(CGameOverController, (m_pBee,m_pImageLife3, m_pImageLife2, m_pImageLife1)));
	m_pBee->AddComponent(NEW(CText, (m_pBee, String("data/fonts/font.png"), String("0"), 50.0, 35.0)));
	AddEntity(m_pBee);
	//AddEnemy
	m_pEnemy = NEW(CEntity2, ("Enemy"));
	m_pEnemy->SetPosition(700.0f, 625.0f);
	m_pEnemy->SetScale(0.25f, 0.25f);
	m_pEnemy->AddComponent(NEW(CAnimator, (m_pEnemy, "data/images/rock-obstacle.png")));
	m_pEnemy->AddComponent(NEW(CVelocity, (m_pEnemy)));
	m_pEnemy->AddComponent(NEW(CAIController, (m_pEnemy, 250.0f, g_widthScreen + 60.0f)));
	AddEntity(m_pEnemy);

	return 0;
}

