#include "stdafx.h"
#include "Stage1.h"
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
#include "KeyMgr.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/TestBackGround.bmp", L"TestBackGround");
	CSoundMgr::Get_Instance()->Initialize();
	g_fVolume = 0.03f;
	CSoundMgr::Get_Instance()->PlayBGM(L"JailField.wav", g_fVolume);

	CObj* pPlayer = new CPlayer;
	pPlayer->Initialize();
	CObjMgr::Get_Instance()->Add_Object(PLAYER, pPlayer);

	CObj* pMouse = new CMouse;
	pMouse->Initialize();
	CObjMgr::Get_Instance()->Add_Object(MOUSE, pMouse);

	CWeapon* pWeapon = new CSword();
	pWeapon->Initialize();

	pWeapon->AttachToPlayer(dynamic_cast<CPlayer*>(pPlayer));
	CObjMgr::Get_Instance()->Add_Object(WEAPON, pWeapon);

	CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(1024, 515, 2048, 170));  //메인 지형

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

}

void CStage1::Update()
{
	CScene::Update();
}

void CStage1::Late_Update()
{
	CScene::Late_Update();
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
	{
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_STAGE2);
		return;
	}

}

void CStage1::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(L"TestBackGround");

	BitBlt(hDC, iScrollX, iScrollY, 2048, 600, hMemDC, 0, 0, SRCCOPY);
	
	CScene::Render(hDC);
}

void CStage1::Release()
{
	CSoundMgr::Destroy_Instance();
	CObjMgr::Get_Instance()->Delete_Object(UI);
	CObjMgr::Get_Instance()->Delete_Object(WEAPON);
	CObjMgr::Get_Instance()->Delete_Object(MOUSE);
	CObjMgr::Get_Instance()->Delete_Object(FLOOR);
	CObjMgr::Get_Instance()->Delete_Object(PLAYER);
}

	
