#include "stdafx.h"
#include "Line.h"
#include "ScrollMgr.h"



CLine::CLine()
{
}

CLine::CLine(LINEPOINT & tLeft, LINEPOINT & tRight)
	: m_tInfo(tLeft, tRight)
{
}


CLine::~CLine()
{
}

void CLine::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	

	MoveToEx(hDC, (float)m_tInfo.tLeft.fX + iScrollX, (float)m_tInfo.tLeft.fY + 37.5, nullptr);
	LineTo(hDC, (float)m_tInfo.tRight.fX + iScrollX, (float)m_tInfo.tRight.fY + 37.5);
}
