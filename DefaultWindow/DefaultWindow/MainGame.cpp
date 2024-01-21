#include "stdafx.h"
#include "MainGame.h"

#include "Mouse.h"

#include "Obj.h"

#include "AbstactFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"


CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_pPlayer(nullptr)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Initialize();
	}
	CLineMgr::Get_Instance()->Initialize();
	m_ObjList[MOUSE].push_back(CAbstractFactory<CMouse>::Create());
}

void CMainGame::Update()
{
	m_pPlayer->Update();

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
	
	m_pPlayer->Render(m_DC);

	for (size_t i = 0; i < END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_DC);
	}

	CLineMgr::Get_Instance()->Render(m_DC);
}

void CMainGame::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);

	for (size_t i = 0; i < END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_DC);
}
