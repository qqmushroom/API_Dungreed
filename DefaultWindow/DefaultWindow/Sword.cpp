#include "stdafx.h"
#include "Sword.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
CSword::CSword()
{
}


CSword::~CSword()
{
}

void CSword::Initialize()
{
	CWeapon::Initialize();

	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 57.f;
	
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Weapon/Sword/Sword.bmp", L"Sword");

	m_pFrameKey = L"Sword";

	m_tFrame = { 0, 0, 0, 200, GetTickCount() };

	m_dwAttackTime = 1000;
}

int CSword::Update()
{
	CWeapon::Update();

	if (m_bIsAttack)
	{
		if (m_dwAttackStartTime + m_dwAttackTime <= GetTickCount())
		{
			m_bIsAttack = false;
		}
	}

	return OBJ_NOEVENT;
}

void CSword::Late_Update()
{
	CWeapon::Late_Update();
}

void CSword::Render(HDC hDC)
{
	CWeapon::Render(hDC);
	
	if (m_bIsAttack)
	{
		RECT tAttackRect = MakeAttackRect();

		Ellipse(hDC, tAttackRect.left, tAttackRect.top, tAttackRect.right, tAttackRect.bottom);
	}
}

void CSword::Release()
{
	CWeapon::Release();
}

void CSword::Attack()
{
	if (m_bIsAttack)
	{
		return;
	}
	POINT ptMouse{};
	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);

	m_tAttackStartInfo.fCX = 100;
	m_tAttackStartInfo.fCY = 100;

	m_tAttackStartInfo.fX = (float)ptMouse.x;
	m_tAttackStartInfo.fY = (float)ptMouse.y;

	m_dwAttackStartTime = GetTickCount();
	m_bIsAttack = true;

	float	g_fVolume(0.05f);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"Swing.wav", SOUND_EFFECT, g_fVolume);

}