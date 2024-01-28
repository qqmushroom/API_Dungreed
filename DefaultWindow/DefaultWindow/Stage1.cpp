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


CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
}

void CStage1::Initialize()
{
	CLineMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/dungeon_boss.bmp", L"dungeon_boss");

	// CObjMgr::Get_Instance()->Add_Object(PLAYER, CAbstractFactory<CPlayer>::Create());

	// 2024.01.22 bskim: ���콺 ȣ���ϴµ� �־� �߻����丮 �������� ���� ���x, Obj����Ʈ PLAYER�� ������ ����־���.

	CObj*pPlayer = new CPlayer;
	pPlayer->Initialize();
	m_ObjList[PLAYER].push_back(pPlayer);

	CObj*pBoss = new CBoss;
	pBoss->Initialize();
	m_ObjList[BOSS].push_back(pBoss);


	CObj*pMouse = new CMouse;
	pMouse->Initialize();
	m_ObjList[MOUSE].push_back(pMouse);

	CWeapon* pWeapon = new CSword();
	pWeapon->Initialize();

	pWeapon->AttachToPlayer(dynamic_cast<CPlayer*>(pPlayer));
	m_ObjList[WEAPON].push_back(pWeapon);

	/*
	CObj * pWeapon = new CWeapon;
	pWeapon->Initialize();
	m_ObjList[WEAPON].push_back(pWeapon);
	*/
	// dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Weapon(&m_ObjList[WEAPON]);

	//// �÷��̾� ��ġ
	//CObjMgr::Get_Instance()->GetBack(PLAYER)->Set_Pos(300, 400);

	//// ����
	//CObjMgr::Get_Instance()->Add_Object(FLOOR, new CBox(100, 600, 1000, 200));			// ���� ����
}

void CStage1::Update()
{
	// 2024.01.22 bskim: �ؿ� obj����Ʈ�δ� ������ ���콺�� ȣ��, �÷��̾�� ������ �����⿡ ��� cobj* m_pPlayer��� ���� ���� ����� Update, Render ���� ȣ���߾���.
	// 2024.01.22 bskim: ���Ͱ��� ������ �߰��� ����Ʈ������ cpp�� LateUpdate ���ΰ��ӿ� �߰����� �ʾ� �÷��̾��� �ִϸ��̼��� ����� �������� ����. 
	
	for (size_t i = 0; i < END; ++i)
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
	}
	//CObjMgr::Get_Instance()->Update();
}

void CStage1::Late_Update()
{
	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
	//CObjMgr::Get_Instance()->Late_Update();
}

void CStage1::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(L"dungeon_boss");

	BitBlt(hDC, iScrollX, iScrollY, 1280, 720, hMemDC, 0, 0, SRCCOPY);

	//2024.01.22 bskim: ��� ���� ũ�⿡ �°� �����°� �÷��̾� ��ġ(�Ǵ� �����浹��Ȳ) ���� �ʿ�

	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(hDC);
	}

	//2024.01.25 bskim: ��� ���� �÷��̾� ���߿� �׷��� �÷��̾� ����
	//2024.01.25 bskim: ��� �����Ÿ��°� �����ϱ��ϱ����� ���� ���۸�

	CLineMgr::Get_Instance()->Render(hDC);

	//CObjMgr::Get_Instance()->Render(hDC);
}

void CStage1::Release()
{
}
