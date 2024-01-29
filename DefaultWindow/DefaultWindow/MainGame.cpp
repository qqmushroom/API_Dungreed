#include "stdafx.h"
#include "MainGame.h"
#include "BmpMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()) // 2024.01.25 bskim: 겟틱카운트는 현재시간을 의미
{

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	//CLineMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Map/back.bmp", L"back");
	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::SC_MENU);
	CSoundMgr::Get_Instance()->Initialize();
	
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(L"back");
	HDC hGroundDC = CBmpMgr::Get_Instance()->Get_Image(L"dungeon_boss");
	
	CSceneMgr::Get_Instance()->Render(hMemDC);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hMemDC, 0, 0, SRCCOPY);

}

void CMainGame::Release()
{
	/*for (size_t i = 0; i < END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}*/

	CBmpMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
