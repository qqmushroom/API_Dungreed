#include "stdafx.h"
#include "Bullet.h"
#include "ScrollMgr.h"
#include "Boss.h"
#include "ObjMgr.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	/*if (m_dwAI_StartTime + m_dwAI_EndTime >= GetTickCount())
	{
		CObj* pPlayer = CObjMgr::GetInstance()->GetBack(PLAYER);

		m_vecDir = Vector2D(pPlayer->Get_Info().fX - Get_Info().fX, pPlayer->Get_Info().fY - Get_Info().fY);
	}

	Vector2D vecDir = m_vecDir.Normalized();*/

	/*m_tInfo.fX += vecDir.fX * m_fSpeed;
	m_tInfo.fY += vecDir.fY * m_fSpeed;*/

	Vector2D vecDir = m_vecDir.Normalized();
	
	m_tInfo.fX += vecDir.fX * m_fSpeed;
	m_tInfo.fY += vecDir.fY * m_fSpeed;


	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	
}

void CBullet::Render(HDC hDC)
{
	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	Ellipse(hDC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);
}

void CBullet::Release()
{
}