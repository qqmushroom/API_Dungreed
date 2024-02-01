#include "stdafx.h"
#include "Sword.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
#include "ScrollMgr.h"
#include "Vector2D.h"
#include "ObjMgr.h"
#include "Boss.h"
#include "SwordAttack.h"


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
	
	/*if (m_bIsAttack)
	{
		RECT tAttackRect = MakeAttackRect();

		int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
		int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

		Ellipse(hDC, tAttackRect.left + iScrollX, tAttackRect.top + iScrollY, tAttackRect.right + iScrollX, tAttackRect.bottom + iScrollY);
	}*/
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

	Vector2D vMouse = Vector2D((float)ptMouse.x, (float)ptMouse.y);

	int	iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int	iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	vMouse.fX += -iScrollX;
	vMouse.fY += -iScrollY;

	CObj* pPlayer = CObjMgr::Get_Instance()->GetBack(PLAYER);

	if (pPlayer != nullptr)
	{
		vMouse.fX = vMouse.fX - pPlayer->Get_Info().fX;
		vMouse.fY = vMouse.fY - pPlayer->Get_Info().fY;

	// 2024.02.01 bskim: t.info fx fy를 원점으로 만들기 위해 px py에서 fx fy를 빼줌
	}

	vMouse = vMouse.Normalized();
	vMouse.fX *= 30;
	vMouse.fY *= 30;

	// 2024.02.01 bskim: 벡터는 원점을 0, 0으로 만들어놓고 방향을 설정한다음 벡터값을 임의로 1로 설정한다음 내가 원하는 값으로 넣어서 구현

	/*m_tAttackStartInfo.fX = vMouse.fX + pPlayer->Get_Info().fX;
	m_tAttackStartInfo.fY = vMouse.fY + pPlayer->Get_Info().fY;*/

	CSwordAttack* pSwordAttack = new CSwordAttack;
	if (pSwordAttack != nullptr)
	{
		pSwordAttack->Initialize();
		pSwordAttack->Set_Pos(vMouse.fX + pPlayer->Get_Info().fX, 
											vMouse.fY + pPlayer->Get_Info().fY + 10);

		pSwordAttack->SetAttackDir(vMouse.Normalized());

		CObjMgr::Get_Instance()->Add_Object(PLAYER_BULLET, pSwordAttack);
	}


	m_dwAttackStartTime = GetTickCount();
	m_bIsAttack = true;

	float	g_fVolume(0.05f);

	CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"Swing.wav", SOUND_EFFECT, g_fVolume);

}