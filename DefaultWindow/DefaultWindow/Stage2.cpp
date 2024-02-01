#include "stdafx.h"
#include "Stage2.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "Weapon.h"
#include "Sword.h"
#include "Boss.h"
#include "SceneMgr.h"
#include "LineMgr.h"
#include "Box.h"
#include "Mouse.h"
#include "SoundMgr.h"
#include "Obj.h"
#include "BossLeftHand.h"
#include "BossRightHand.h"
#include "Sprite.h"
#include "ProgressBar.h"
#include "BossSprite.h"
#include "BossProgressBar.h"
CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
}

void CStage2::Initialize()
{
	//CLineMgr::Get_Instance()->Initialize();
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/dungeon_boss.bmp", L"dungeon_boss");
	CSoundMgr::Get_Instance()->Initialize();
	g_fVolume = 0.03f;
	CSoundMgr::Get_Instance()->PlayBGM(L"JailBoss.wav", g_fVolume);
	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"JailBossEnterence.wav", SOUND_EFFECT, g_fVolume);

	// CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());
	// 2024.01.22 bskim: 마우스 호출하는데 있어 추상팩토리 이해하지 못해 사용x, Obj리스트 PLAYER에 데이터 비어있었음.

	CObj* pBossLeftHand = new CBossLeftHand;
	pBossLeftHand->Initialize();
	CObjMgr::Get_Instance()->Add_Object(BOSSLEFTHAND, pBossLeftHand);

	CObj* pBossRightHand = new CBossRightHand;
	pBossRightHand->Initialize();
	CObjMgr::Get_Instance()->Add_Object(BOSSRIGHTHAND, pBossRightHand);

	CObj* pPlayer = new CPlayer;
	pPlayer->Initialize();
	CObjMgr::Get_Instance()->Add_Object(PLAYER, pPlayer);


	CObj* pBoss = new CBoss;
	pBoss->Initialize();
	CObjMgr::Get_Instance()->Add_Object(BOSS, pBoss);

	CObj* pMouse = new CMouse;
	pMouse->Initialize();
	CObjMgr::Get_Instance()->Add_Object(MOUSE, pMouse);

	CWeapon* pWeapon = new CSword();
	pWeapon->Initialize();

	pWeapon->AttachToPlayer(dynamic_cast<CPlayer*>(pPlayer));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, pWeapon);

	/*
	CObj * pWeapon = new CWeapon;
	pWeapon->Initialize();
	m_ObjList[WEAPON].push_back(pWeapon);
	*/
	//dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Weapon(&m_ObjList[WEAPON]);

	//// 플레이어 위치
	//CObjMgr::Get_Instance()->GetBack(PLAYER)->Set_Pos(300, 400);


	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(640, 645, 1280, 110));  //메인 지형
	
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(636, 485, 435, 15));    //중앙 지형
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(636, 175, 235, 35));

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(270, 375, 150, 17));    //왼쪽 지형
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(265, 245, 120, 17));

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(1000, 375, 150, 17));   //오른쪽 지형
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(1005, 245, 120, 17));

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(640, 30, 1020, 60));    //천장

	CSprite* pHpBarBack = new CSprite;
	if (pHpBarBack != nullptr)
	{
		pHpBarBack->SetImagePath(L"../Image/UI/PlayerLifeBack.bmp", L"PlayerLifeBack");
		pHpBarBack->SetInfo(160, 40, 300, 65);

		CObjMgr::Get_Instance()->Add_Object(UI, pHpBarBack);
	}

	CProgressBar* pHpBar = new CProgressBar;
	if (pHpBar != nullptr)
	{
		pHpBar->SetImagePath(L"../Image/UI/PlayerLifeBack2.bmp", L"PlayerLifeBack2");
		pHpBar->SetInfo(160, 40, 300, 65);

		pHpBar->SetTarget(pPlayer);

		CObjMgr::Get_Instance()->Add_Object(UI, pHpBar);
	}

	CBossSprite* pBossHpBarBack = new CBossSprite;
	if (pBossHpBarBack != nullptr)
	{
		pBossHpBarBack->SetImagePath(L"../Image/UI/BossLifeBack.bmp", L"BossLifeBack");
		pBossHpBarBack->SetInfo(400, 570, 375, 48);

		CObjMgr::Get_Instance()->Add_Object(UI, pBossHpBarBack);
	}

	CBossProgressBar* pBossHpBar = new CBossProgressBar;
	if (pBossHpBar != nullptr)
	{
		pBossHpBar->SetImagePath(L"../Image/UI/BossLifeBar.bmp", L"BossLifeBar");
		pBossHpBar->SetInfo(427, 569, 300, 30);

		pBossHpBar->SetTarget(pBoss);

		CObjMgr::Get_Instance()->Add_Object(UI, pBossHpBar);
	}

}

void CStage2::Update()
{
	// 2024.01.22 bskim: 밑에 obj리스트로는 그전에 마우스만 호출, 플레이어는 데이터 없었기에 계속 cobj* m_pPlayer라는 변수 따로 만들어 Update, Render 마다 호출했었음.
	// 2024.01.22 bskim: 위와같은 이유에 추가로 디폴트윈도우 cpp에 LateUpdate 메인게임에 추가하지 않아 플레이어의 애니매이션이 제대로 동작하지 못함. 
	
	/*for (size_t i = 0; i < END; ++i)
	{
		for (auto iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); )
		{
			int iResult = (*iter)->Update();

			if (OBJ_DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}*/
	CScene::Update();
}

void CStage2::Late_Update()
{
	/*for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}*/
	CScene::Late_Update();
}

void CStage2::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(L"dungeon_boss");

	BitBlt(hDC, iScrollX, iScrollY, 1280, 720, hMemDC, 0, 0, SRCCOPY);
	//2024.01.22 bskim: 배경 사진 크기에 맞게 오프셋과 플레이어 위치(또는 라인충돌상황) 수정 필요

	/*for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}*/
	//2024.01.25 bskim: 배경 먼저 플레이어 나중에 그래야 플레이어 보임
	//2024.01.25 bskim: 배경 깜빡거리는거 방지하기하기위해 더블 버퍼링

	//CLineMgr::Get_Instance()->Render(hDC);
	CScene::Render(hDC);
	/*CObjMgr::Get_Instance()->Render(hDC);*/
}

void CStage2::Release()
{
	CSoundMgr::Destroy_Instance();
}
