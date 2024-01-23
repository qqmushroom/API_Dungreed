#include "stdafx.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "Mouse.h"
#include "Obj.h"
#include "AbstactFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "Weapon.h"


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

	CObj*pPlayer = new CPlayer;
	pPlayer->Initialize();
	m_ObjList[PLAYER].push_back(pPlayer);
	
	// 2024.01.22 bskim: ���콺 ȣ���ϴµ� �־� �߻����丮 �������� ���� ���x, Obj����Ʈ PLAYER�� ������ ����־���.

	CObj*pMouse = new CMouse;
	pMouse ->Initialize();
	m_ObjList[MOUSE].push_back(pMouse);


	//CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/Ground.bmp", L"Ground");

	/*
	CObj * pWeapon = new CWeapon;
	pWeapon->Initialize();
	m_ObjList[WEAPON].push_back(pWeapon);
	*/
	// dynamic_cast<CPlayer*>(m_ObjList[PLAYER].front())->Set_Weapon(&m_ObjList[WEAPON]);
	
}

void CMainGame::Update()
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
	Rectangle(m_DC, 0, 0, WINCX, WINCY);

	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}

	CLineMgr::Get_Instance()->Render(m_DC);
	//HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(L"Ground");
	//HDC hGroundDC = CBmpMgr::Get_Instance()->Get_Image(L"TestBackGround");
	//BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);
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
