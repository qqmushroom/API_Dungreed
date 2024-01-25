#include "stdafx.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "Mouse.h"
#include "Obj.h"
#include "AbstactFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "Weapon.h"
#include "Sword.h"
#include "ScrollMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount()) 
{

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	CLineMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/back.bmp", L"back");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/dungeon_boss.bmp", L"dungeon_boss");

	//CObj*pPlayer = new CPlayer;
	//pPlayer->Initialize();
	//m_ObjList[PLAYER].push_back(pPlayer);
	
	// 2024.01.22 bskim: 마우스 호출하는데 있어 추상팩토리 이해하지 못해 사용x, Obj리스트 PLAYER에 데이터 비어있었음.

	CObj*pPlayer = new CPlayer;
	pPlayer->Initialize();
	m_ObjList[PLAYER].push_back(pPlayer);


	CObj*pMouse = new CMouse;
	pMouse ->Initialize();
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
	
}

void CMainGame::Update()
{
	// 2024.01.22 bskim: 밑에 obj리스트로는 그전에 마우스만 호출, 플레이어는 데이터 없었기에 계속 cobj* m_pPlayer라는 변수 따로 만들어 Update, Render 마다 호출했었음.
	// 2024.01.22 bskim: 위와같은 이유에 추가로 디폴트윈도우 cpp에 LateUpdate 메인게임에 추가하지 않아 플레이어의 애니매이션이 제대로 동작하지 못함. 
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
}

void CMainGame::Late_Update()
{

	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}
}

void CMainGame::Render()
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(L"back");
	HDC hGroundDC = CBmpMgr::Get_Instance()->Get_Image(L"dungeon_boss");
	BitBlt(hMemDC, iScrollX, iScrollY, 1280, 720, hGroundDC, 0, 0, SRCCOPY);
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}

	CLineMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Release()
{

	for (size_t i = 0; i < END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
