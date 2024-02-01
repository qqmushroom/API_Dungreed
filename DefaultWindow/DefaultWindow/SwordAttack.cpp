#include "stdafx.h"
#include "SwordAttack.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CSwordAttack::CSwordAttack()
{
}

CSwordAttack::~CSwordAttack()
{
}

void CSwordAttack::Initialize()
{
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Weapon/SwordEffect/SwordEffectVersion1.bmp", L"SwordEffectVersion1");

	m_pFrameKey = L"SwordEffectVersion1";

	m_tFrame = { 0, 2, 0, 200, GetTickCount() };

    m_tInfo.fCX = 100.f;
    m_tInfo.fCY = 108.f;

	m_dwAttackStartTime = GetTickCount();
	m_dwAttackTime = 600;
}

int CSwordAttack::Update()
{
	if (m_dwAttackStartTime + m_dwAttackTime <= GetTickCount())
	{
		return OBJ_DEAD;
	}

    return OBJ_NOEVENT;
}

void CSwordAttack::Late_Update()
{
	__super::Update_Rect();

	Move_Frame();
}

void CSwordAttack::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left + iScrollX,
		m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달
}

void CSwordAttack::Release()
{
}

void CSwordAttack::SetAttackDir(Vector2D vDir)
{
	float fCosAngle = acos(vDir.fX) * 180 / PI;

	if (vDir.fY > 0)
	{
		fCosAngle = 360 - fCosAngle;
	}

	for (int i = 7; i >= 0; --i)
	{
		float fStartAngle = 112.5f + 45.f * (7 - i);
		float fEndAngle = fStartAngle + 45.f;

		if (fEndAngle > 360 && fCosAngle < 90)
		{
			fCosAngle += 360;
		}

		if (fStartAngle <= fCosAngle && fCosAngle <= fEndAngle)
		{
			m_tFrame.iMotion = i;
			break;
		}
	}
}
