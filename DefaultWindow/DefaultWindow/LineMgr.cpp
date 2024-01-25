#include "stdafx.h"
#include "LineMgr.h"

CLineMgr*	CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	LINEPOINT	tLine[2] =
	{
		{ 100.f, 500.f },
		{ 3000.f, 500.f }

	};
	m_LineList.push_back(new CLine(tLine[0], tLine[1]));
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& iter : m_LineList)
		iter->Render(hDC);
}

void CLineMgr::Release()
{
	for_each(m_LineList.begin(), m_LineList.end(), Safe_Delete<CLine*>);
	m_LineList.clear();
}

bool CLineMgr::Collision_Line(float _fX, float * _pY)
{
	if (m_LineList.empty())
		return false;

	CLine*	pTarget = nullptr;

	for (auto& iter : m_LineList)
	{
		if (_fX >= iter->Get_Info().tLeft.fX &&
			_fX < iter->Get_Info().tRight.fX)
		{
			pTarget = iter;
		}
	}

	if (!pTarget)
		return false;


	float x1 = pTarget->Get_Info().tLeft.fX;
	float y1 = pTarget->Get_Info().tLeft.fY;
	float x2 = pTarget->Get_Info().tRight.fX;
	float y2 = pTarget->Get_Info().tRight.fY;

	*_pY = ((y2 - y1) / (x2 - x1)) * (_fX - x1) + y1;

	return true;
}
