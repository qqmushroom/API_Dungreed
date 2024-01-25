#include "stdafx.h"
#include "Weapon.h"
#include "Player.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
	Release();
}

void CWeapon::Initialize()
{
	
}

int CWeapon::Update()
{
	if (m_pPlayerOwner != nullptr)
	{
		m_tInfo.fX = m_pPlayerOwner->Get_Info().fX;
		m_tInfo.fY = m_pPlayerOwner->Get_Info().fY;

	}
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CWeapon::Late_Update()
{
}

void CWeapon::Render(HDC hDC)
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

void CWeapon::Release()
{
}

void CWeapon::AttachToPlayer(CPlayer* pPlayer)
{
	if (pPlayer == nullptr)
	{
		return;
	}

	m_pPlayerOwner = pPlayer;
	m_pPlayerOwner->AddWeapon(this);
	
}

RECT CWeapon::MakeAttackRect()
{
	RECT tRect;

	tRect.left = LONG(m_tAttackStartInfo.fX - (m_tAttackStartInfo.fCX * 0.5f));
	tRect.top = LONG(m_tAttackStartInfo.fY - (m_tAttackStartInfo.fCY * 0.5f));
	tRect.right = LONG(m_tAttackStartInfo.fX + (m_tAttackStartInfo.fCX * 0.5f));
	tRect.bottom = LONG(m_tAttackStartInfo.fY + (m_tAttackStartInfo.fCY * 0.5f));

	return tRect;
}
