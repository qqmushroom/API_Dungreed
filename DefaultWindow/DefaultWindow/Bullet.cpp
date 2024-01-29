#include "stdafx.h"
#include "Bullet.h"
#include "ScrollMgr.h"
#include "Boss.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CBullet::CBullet():
 m_ePreState(ST_END), m_eCurState(IDLE)
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fSpeed = 4.f;

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Boss/BossBullet.bmp", L"BossBullet");

	m_pFrameKey = L"BossBullet";

	m_tFrame = { 0, 9, 0, 200, GetTickCount() };
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if (m_dwAI_StartTime + m_dwAI_EndTime >= GetTickCount())
	{
		CObj* pPlayer = CObjMgr::GetInstance()->GetBack(PLAYER);

		m_vecDir = Vector2D(pPlayer->Get_Info().fX - Get_Info().fX, pPlayer->Get_Info().fY - Get_Info().fY);
	}*/

	Vector2D vecDir = m_vecDir.Normalized();

	m_tInfo.fX += vecDir.fX * m_fSpeed;
	m_tInfo.fY += vecDir.fY * m_fSpeed;

	/*Vector2D vecDir = m_vecDir.Normalized();*/
	
	
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	Move_Frame();
	Motion_Change();
}

void CBullet::Render(HDC hDC)
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

void CBullet::Release()
{
}

void CBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}

}
