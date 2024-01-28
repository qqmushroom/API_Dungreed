#include "stdafx.h"
#include "Boss.h"
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Define.h"

CBoss::CBoss() :
	m_iBoss_Hp(0), m_ePreState(ST_END), m_eCurState(IDLE)
{
}
CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 175.f;
	m_tInfo.fCY = 248.f;
	m_tInfo.fX = 630.f;
	m_tInfo.fY = 350.f;
	m_iBoss_Hp = 100;

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Boss/BossIdle.bmp", L"BossIdle");

	m_pFrameKey = L"BossIdle";

	m_tFrame = { 0, 9, 0, 600, GetTickCount() };
}

int CBoss::Update()
{
	/*if (m_bDead)
		return OBJ_DEAD;*/


	/*Boss_Attack();*/

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss::Late_Update()
{
	Move_Frame();
	Motion_Change();
}

void CBoss::Render(HDC hDC)
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

void CBoss::Release()
{
}

void CBoss::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iFrameStart = 0;
			m_tFrame.iFrameEnd = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 600;
			m_tFrame.dwTime = GetTickCount();
			break;
		}

		m_ePreState = m_eCurState;
	}

}

//void CBoss::Boss_Attack()
//{
//	DWORD CurrTickTime = GetTickCount();
//
//
//	for (int i = 0; i < FIRE_MAX; ++i)
//	{
//		if (m_dwLastFireTIme[i] + m_fFireTime[i] <= CurrTickTime)
//		{
//			//
//			switch (i)
//			{
//			case FIRE_0:
//				CObjMgr::GetInstance()->AddObject(BOSSBULLET, CAbstractFactory<CBossBulletMulti>::CreateObj());
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->Set_Pos(Get_Info().fX, Get_Info().fY);
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->SetDir(Vector2D(-1, 1));
//
//				CObjMgr::GetInstance()->AddObject(BOSSBULLET, CAbstractFactory<CBossBulletMulti>::CreateObj());
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->Set_Pos(Get_Info().fX, Get_Info().fY);
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->SetDir(Vector2D(0, 1));
//
//				CObjMgr::GetInstance()->AddObject(BOSSBULLET, CAbstractFactory<CBossBulletMulti>::CreateObj());
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->Set_Pos(Get_Info().fX, Get_Info().fY);
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->SetDir(Vector2D(1, 1));
//				break;
//
//			case FIRE_1:
//				CObjMgr::GetInstance()->AddObject(BOSSBULLET, CAbstractFactory<CBossBulletAI>::CreateObj());
//				dynamic_cast<CBossBulletAI*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->Set_Pos(Get_Info().fX, Get_Info().fY);
//				break;
//
//			default:
//				break;
//			}
//
//			m_dwLastFireTIme[i] = CurrTickTime;
//		}
//	}
//}

//void CBoss::Take_Damage(int _iDamage)
//{
//	m_iBoss_Hp -= _iDamage;
//	if (m_iHp <= 0)
//	{
//		m_iHp = 0;
//
//		Set_Dead();
//	}
//}

