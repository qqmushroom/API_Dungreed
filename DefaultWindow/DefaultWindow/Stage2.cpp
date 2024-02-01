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
	// 2024.01.22 bskim: ���콺 ȣ���ϴµ� �־� �߻����丮 �������� ���� ���x, Obj����Ʈ PLAYER�� ������ ����־���.

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

	//// �÷��̾� ��ġ
	//CObjMgr::Get_Instance()->GetBack(PLAYER)->Set_Pos(300, 400);


	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(640, 645, 1280, 110));  //���� ����
	
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(636, 485, 435, 15));    //�߾� ����
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(636, 175, 235, 35));

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(270, 375, 150, 17));    //���� ����
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(265, 245, 120, 17));

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(1000, 375, 150, 17));   //������ ����
	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(1005, 245, 120, 17));

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(640, 30, 1020, 60));    //õ��

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
	// 2024.01.22 bskim: �ؿ� obj����Ʈ�δ� ������ ���콺�� ȣ��, �÷��̾�� ������ �����⿡ ��� cobj* m_pPlayer��� ���� ���� ����� Update, Render ���� ȣ���߾���.
	// 2024.01.22 bskim: ���Ͱ��� ������ �߰��� ����Ʈ������ cpp�� LateUpdate ���ΰ��ӿ� �߰����� �ʾ� �÷��̾��� �ִϸ��̼��� ����� �������� ����. 
	
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
	//2024.01.22 bskim: ��� ���� ũ�⿡ �°� �����°� �÷��̾� ��ġ(�Ǵ� �����浹��Ȳ) ���� �ʿ�

	/*for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}*/
	//2024.01.25 bskim: ��� ���� �÷��̾� ���߿� �׷��� �÷��̾� ����
	//2024.01.25 bskim: ��� �����Ÿ��°� �����ϱ��ϱ����� ���� ���۸�

	//CLineMgr::Get_Instance()->Render(hDC);
	CScene::Render(hDC);
	/*CObjMgr::Get_Instance()->Render(hDC);*/
}

void CStage2::Release()
{
	CSoundMgr::Destroy_Instance();
}
