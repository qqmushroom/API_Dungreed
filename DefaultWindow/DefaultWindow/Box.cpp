#include "stdafx.h"
#include "Box.h"
#include "ScrollMgr.h"

CBox::CBox()
{
}

CBox::CBox(float _fX, float _fY, float _fCX, float _fCY)
{
	m_tInfo = { _fX, _fY, _fCX, _fCY };

	CObj::Update_Rect();
}

CBox::~CBox()
{
	Release();
}

void CBox::Initialize()
{
	//CObj::Update_Rect();
}

int CBox::Update()
{
	return OBJ_NOEVENT;
}

void CBox::Late_Update()
{
	int     iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int     iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

}

void CBox::Render(HDC hDC)
{
	/*if (!m_bActive)
		return;*/
	// 2023.01.28 숨기려고 만든 변수
	int     iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int     iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	Rectangle(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		m_tRect.right + iScrollX,
		m_tRect.bottom + iScrollY
	);
}

void CBox::Release()
{
}

void CBox::SetPos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;

	CObj::Update_Rect();
}
