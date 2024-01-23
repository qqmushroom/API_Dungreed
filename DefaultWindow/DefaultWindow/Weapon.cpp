#include "stdafx.h"
#include "Weapon.h"


CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
	Release();
}

void CWeapon::Initialize()
{
	m_tInfo.fCX = 7.f;
	m_tInfo.fCY = 18.f;
}

int CWeapon::Update()
{
	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CWeapon::Late_Update()
{
}

void CWeapon::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWeapon::Release()
{
}
