#pragma once

#include "Define.h"
#include "Player.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Late_Update();
	void		Render();
	void		Release();

private:
	HDC			m_DC;
	CObj*		m_pPlayer;
	DWORD	    m_dwTime;

	list<CObj*>		m_ObjList[END];

};

