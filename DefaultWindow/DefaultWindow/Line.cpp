#include "stdafx.h"
#include "Line.h"


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
	MoveToEx(hDC, (float)m_tInfo.tLeft.fX, (float)m_tInfo.tLeft.fY + 37.5, nullptr);
	LineTo(hDC, (float)m_tInfo.tRight.fX, (float)m_tInfo.tRight.fY + 37.5);
}
