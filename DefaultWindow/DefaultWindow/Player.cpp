#include "stdafx.h"
#include "Player.h"

#include "LineMgr.h"
#include "KeyMgr.h"

#include "Define.h"
CPlayer::CPlayer()
	:m_bJump(false), m_fJumpPower(0.f), m_fTime(0.f)
{

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f };
	m_fSpeed = 10.f;
	m_fJumpPower = 16.f;
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
	
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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
		m_eDir = DIR_RIGHT;
		if (!m_bJump && CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;
	}

	if (KEY_PRESS('A'))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eDir = DIR_LEFT;
		if (!m_bJump && CLineMgr::Get_Instance()->Collision_Line(m_tInfo.fX, &fY))
			m_tInfo.fY = fY;
	}

	if (KEY_DOWN(VK_SPACE))
		m_bJump = true;
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