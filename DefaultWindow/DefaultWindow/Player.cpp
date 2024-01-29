#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "Define.h"
#include "Weapon.h"
#include "Sword.h"
#include "Obj.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

float	g_fVolume(0.05f);

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
	m_tInfo = { 200.f, 450.f, 78.f, 75.f };
	m_fSpeed = 7.f;
	m_fJumpPower = 15.f;
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Player/Idle/CharIdle.bmp", L"CharIdle");
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Player/Run/CharRun.bmp", L"CharRun");
	

	m_pFrameKey = L"CharIdle";

	m_tFrame = { 0, 4, 0, 200, GetTickCount() };

	CSoundMgr::Get_Instance()->PlayBGM(L"JailBoss.wav", g_fVolume);
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
	Offset();
}

void CPlayer::Render(HDC hDC)
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

void CPlayer::Release()
{

}

void CPlayer::OnHit()
{
	CObj::OnHit();
	JumpEnd();
}

void CPlayer::Key_Input()
{

	float	fY(0.f);

	if (KEY_PRESS('D'))
	{
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fX = min(m_tInfo.fX, STAGE_MAX_X);
		m_pFrameKey = L"CharRun";
		m_eCurState = RUN;
		m_eDir = DIR_RIGHT;
		/*if (!m_bJump && CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}
	else if (KEY_PRESS('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fX = max(m_tInfo.fX, STAGE_MIN_X);   //2024.01.26 bskim: min, max 함수를 이용해 최대 움직임 고정(디파인으로 값 설정)
		m_pFrameKey = L"CharRun";
		m_eCurState = RUN2;
		m_eDir = DIR_LEFT;
		/*if (!m_bJump && CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;*/
	}
	else
	{
		m_pFrameKey = L"CharIdle";
		m_eCurState = IDLE;
	}

	if ((KEY_DOWN('W')) || (KEY_DOWN(VK_SPACE)))
	{
		m_bJump = true;
	}

	//else if ((KEY_PRESS('S')) && (KEY_DOWN(VK_SPACE)))
	//{
	//	m_bUnderJump = true;
	//}

	if (KEY_PRESS(VK_LBUTTON))
	{
		if (!m_vecWeapon[m_iCurWeaponIndex]->GetIsAttack())
		{
			m_vecWeapon[m_iCurWeaponIndex]->Attack();

			CSoundMgr::Get_Instance()->PlaySound(L"Swing.wav", SOUND_EFFECT, g_fVolume);
		}
	}
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
	{
		CSoundMgr::Get_Instance()->PlaySound(L"JailBoss.wav", SOUND_EFFECT, g_fVolume);
		return;
	}
	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	{
		g_fVolume -= 0.1f;


		if (0.f > g_fVolume)
			g_fVolume = 0.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fVolume);
	}

	else if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
	{
		g_fVolume += 0.1f;

		if (1.f < g_fVolume)
			g_fVolume = 1.f;

		CSoundMgr::Get_Instance()->SetChannelVolume(SOUND_EFFECT, g_fVolume);

	}
}

void CPlayer::Jump()
{
	float	fY(0.f);


	if (m_bJump)
	{
		m_tInfo.fY -= (m_fJumpPower * m_fTime/*sin(m_fAngle)*/) - (9.8f * m_fTime * m_fTime * 0.6f);

		m_fTime += 0.1f;
	}

	else 
	{
		m_tInfo.fY += 15.f;
	}

}

void CPlayer::JumpEnd()
{
	if (m_bJump)
	{
		m_bJump = false;
		m_fTime = 0.f;
	}
}

//void CPlayer::UnderJump()
//{
//	float	fY(0.f);
//
//	bool bLineCol = CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY);
//
//	if (m_bUnderJump)
//	{
//		m_tInfo.fY -= (m_fJumpPower * m_fTime/*sin(m_fAngle)*/) + (9.8f * m_fTime * m_fTime * 0.5f);
//
//		m_fTime += 0.1f;
//
//		if (bLineCol && (fY > m_tInfo.fY))
//		{
//			m_bUnderJump = false;
//			m_fTime = 0.f;
//			m_tInfo.fY = fY;
//		}
//	}
//
//	else if (bLineCol)
//	{
//		m_tInfo.fY = fY;
//	}
//
//}

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
void CPlayer::Offset()
{
    int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

if (SCROLL_OFFSET_MIN_X  > m_tInfo.fX + iScrollX)
CScrollMgr::Get_Instance()->Set_ScrollX(m_fSpeed);

if (SCROLL_OFFSET_MAX_X  < m_tInfo.fX + iScrollX)
	CScrollMgr::Get_Instance()->Set_ScrollX(-m_fSpeed);

if (SCROLL_OFFSET_MIN_Y > m_tInfo.fY + iScrollY)
CScrollMgr::Get_Instance()->Set_ScrollY(m_fSpeed);

if (SCROLL_OFFSET_MAX_Y < m_tInfo.fY + iScrollY)
	CScrollMgr::Get_Instance()->Set_ScrollY(-m_fSpeed);
}
