#include "stdafx.h"
#include "BossRightLaser.h"
#include "ScrollMgr.h"
#include "Boss.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBossRightLaser::CBossRightLaser()
{
}


CBossRightLaser::~CBossRightLaser()
{
}

void CBossRightLaser::Initialize()
{
	m_tInfo.fCX = 96.f;
	m_tInfo.fCY = 147.f;

	m_tHeadInfo.fCX = 81.f;
	m_tHeadInfo.fCY = 132.f;

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Boss/BossLaserHead.bmp", L"BossLaserHead");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Boss/BossLaserBody.bmp", L"BossLaserBody");

	m_pHeadFrameKey = L"BossLaserHead";
	m_pFrameKey = L"BossLaserBody";
	m_tFrame = { 0, 7, 0, 200, GetTickCount() };
	m_tHeadFrame = { 0, 7, 1, 200, GetTickCount() };

	m_dwTIME = GetTickCount();
	m_iBodyCount = 9;
}

int CBossRightLaser::Update()
{
	if (m_dwTIME + 1400 <= GetTickCount())
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossRightLaser::Late_Update()
{
	Move_Frame();
	Move_HeadFrame();
}

void CBossRightLaser::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hHeadMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pHeadFrameKey);

	GdiTransparentBlt(hDC,
		m_tHeadRect.left + iScrollX,
		m_tHeadRect.top + iScrollY,
		(int)m_tHeadInfo.fCX,
		(int)m_tHeadInfo.fCY,
		hHeadMemDC,
		m_tHeadFrame.iFrameStart * (int)m_tHeadInfo.fCX,
		m_tHeadFrame.iMotion * (int)m_tHeadInfo.fCY,
		(int)m_tHeadInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tHeadInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달


	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	for (int i = 0; i < m_iBodyCount; ++i)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX - m_tHeadInfo.fCX - m_tInfo.fCX * i,
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
}

void CBossRightLaser::Release()
{
}

void CBossRightLaser::Update_Rect()
{
	CObj::Update_Rect();

	m_tHeadRect.left = LONG(m_tInfo.fX - (m_tHeadInfo.fCX * 0.5f));
	m_tHeadRect.top = LONG(m_tInfo.fY - (m_tHeadInfo.fCY * 0.5f));
	m_tHeadRect.right = LONG(m_tInfo.fX + (m_tHeadInfo.fCX * 0.5f));
	m_tHeadRect.bottom = LONG(m_tInfo.fY + (m_tHeadInfo.fCY * 0.5f));
}

void CBossRightLaser::Move_HeadFrame()
{
	if (m_tHeadFrame.dwTime + m_tHeadFrame.dwSpeed < GetTickCount())
	{
		++m_tHeadFrame.iFrameStart;

		if (m_tHeadFrame.iFrameStart > m_tHeadFrame.iFrameEnd)
			m_tHeadFrame.iFrameStart = 0;

		m_tHeadFrame.dwTime = GetTickCount();
	}

}
