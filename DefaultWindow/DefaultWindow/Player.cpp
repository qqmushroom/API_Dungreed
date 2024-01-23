#include "stdafx.h"
#include "Player.h"
#include "AbstactFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "Define.h"
#include "Weapon.h"
#include "Obj.h"

CPlayer::CPlayer()
	:m_bJump(false), m_bUnderJump(false), m_fJumpPower(0.f), m_fTime(0.f), m_ePreState(ST_END), m_eCurState(IDLE)
{

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 78.f, 75.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 16.f;
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Player/Idle/CharIdle.bmp", L"CharIdle");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Player/Run/CharRun.bmp", L"CharRun");
	

	m_pFrameKey = L"CharIdle";

	m_tFrame = { 0, 4, 0, 200, GetTickCount() };

}

int CPlayer::Update()
{

	Key_Input();
	Jump();
	__super::Update_Rect();	

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	Move_Frame();
	Motion_Change();
}

void CPlayer::Render(HDC hDC)
{
	//int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	//int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left, //+ iScrollX,
		m_tRect.top, //+ iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달
}

void CPlayer::Release()
{

}

void CPlayer::Key_Input()
{

	float	fY(0.f);

	if (KEY_PRESS('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_pFrameKey = L"CharRun";
		m_eCurState = RUN;
		m_eDir = DIR_RIGHT;
		if (!m_bJump && CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;
	}
	else if (KEY_PRESS('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_pFrameKey = L"CharRun";
		m_eCurState = RUN2;
		m_eDir = DIR_LEFT;
		if (!m_bJump && CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;
	}
	else if ((KEY_DOWN('W')) || (KEY_DOWN(VK_SPACE)))
	{
		m_bJump = true;
	}
	else if ((KEY_PRESS('S')) && (KEY_DOWN(VK_SPACE)))
	{
		m_bUnderJump = true;
	}
	else if (KEY_PRESS(VK_LBUTTON))
	{
		//Player_Attack();
	}
	else
	{
		m_pFrameKey = L"CharIdle";
		m_eCurState = IDLE;
	}
}

void CPlayer::Jump()
{
	float	fY(0.f);

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bJump)
	{
		m_tInfo.fY -= (m_fJumpPower * m_fTime/*sin(m_fAngle)*/) - (9.8f * m_fTime * m_fTime * 0.5f);

		m_fTime += 0.1f;

		if (bLineCol && (fY < m_tInfo.fY))
		{
			m_bJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}

	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}

}

void CPlayer::UnderJump()
{
	float	fY(0.f);

	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);

	if (m_bUnderJump)
	{
		m_tInfo.fY -= (m_fJumpPower * m_fTime/*sin(m_fAngle)*/) + (9.8f * m_fTime * m_fTime * 0.5f);

		m_fTime += 0.1f;

		if (bLineCol && (fY > m_tInfo.fY))
		{
			m_bUnderJump = false;
			m_fTime = 0.f;
			m_tInfo.fY = fY;
		}
	}

	else if (bLineCol)
	{
		m_tInfo.fY = fY;
	}

}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 4;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case RUN:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case RUN2:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 7;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}

}

