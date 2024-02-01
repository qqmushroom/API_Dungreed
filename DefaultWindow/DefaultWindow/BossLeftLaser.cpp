#include "stdafx.h"
#include "BossLeftLaser.h"
#include "ScrollMgr.h"
#include "Boss.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBossLeftLaser::CBossLeftLaser()
{
}


CBossLeftLaser::~CBossLeftLaser()
{
}

void CBossLeftLaser::Initialize()
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

	m_dwTIME = GetTickCount();
	m_iBodyCount = 9;
}

int CBossLeftLaser::Update()
{
	if (m_dwTIME + 1400 <= GetTickCount())
	{
		return OBJ_DEAD;
	}

	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossLeftLaser::Late_Update()
{
	Move_Frame();
}

void CBossLeftLaser::Render(HDC hDC)
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
		m_tFrame.iFrameStart * (int)m_tHeadInfo.fCX,
		m_tFrame.iMotion * (int)m_tHeadInfo.fCY,
		(int)m_tHeadInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tHeadInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달


	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	for (int i = 0; i < m_iBodyCount; ++i)
	{
		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX + m_tHeadInfo.fCX + m_tInfo.fCX * i,
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

void CBossLeftLaser::Release()
{
}

void CBossLeftLaser::Update_Rect()
{
	CObj::Update_Rect();

	m_tHeadRect.left = LONG(m_tInfo.fX - (m_tHeadInfo.fCX * 0.5f));
	m_tHeadRect.top = LONG(m_tInfo.fY - (m_tHeadInfo.fCY * 0.5f));
	m_tHeadRect.right = LONG(m_tInfo.fX + (m_tHeadInfo.fCX * 0.5f));
	m_tHeadRect.bottom = LONG(m_tInfo.fY + (m_tHeadInfo.fCY * 0.5f));
}


