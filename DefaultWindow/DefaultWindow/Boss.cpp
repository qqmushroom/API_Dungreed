#include "stdafx.h"
#include "Boss.h"
#include "Obj.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "Define.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "Bullet.h"

CBoss::CBoss() :
	m_iBoss_Hp(0), m_ePreState(ST_END), m_eCurState(IDLE), m_iAngle(0), m_iAddAngle(0), m_iBulletCount(0)
{
}
CBoss::~CBoss()
{
}

void CBoss::Initialize()
{
	m_tInfo.fCX = 175.f;
	m_tInfo.fCY = 248.f;
	m_tInfo.fX = 625.f;
	m_tInfo.fY = 345.f;
	m_iBoss_Hp = 150;
	m_iAngle = 0;
	m_iAddAngle = 10;
	m_iBulletCount = 4;

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Boss/BossIdle.bmp", L"BossIdle");

	m_pFrameKey = L"BossIdle";

	m_tFrame = { 0, 9, 0, 600, GetTickCount() };
}

int CBoss::Update()
{
	if (0 >= m_iBoss_Hp)
		return OBJ_DEAD;

	if (m_dwTime + 250 < GetTickCount())
	{

	    Boss_Attack();

	    m_dwTime = GetTickCount();
	}

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

void CBoss::Boss_Attack()
{
	//CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create());
	
	/*CObj* pBullet = new CBullet;
	pBullet->Initialize();
	CObjMgr::Get_Instance()->Add_Object(BULLET, pBullet);
	CObjMgr::Get_Instance()->GetBack(BULLET)->Set_Pos(m_tInfo.fX, m_tInfo.fY);*/


	/*CObjMgr::Get_Instance()->Add_Object(BULLET, CAbstractFactory<CBullet>::Create());
	dynamic_cast<CBullet*>(CObjMgr::Get_Instance()->GetBack(BULLET))->Set_Pos(Get_Info().fX + 15, Get_Info().fY + 30);
	dynamic_cast<CBullet*>(CObjMgr::Get_Instance()->GetBack(BULLET))->SetDir(Vector2D(-1, 1));*/

	for (int i = 0; i < m_iBulletCount; ++i)
	{
		CBullet* pBullet = new CBullet;
		pBullet->Initialize();
		CObjMgr::Get_Instance()->Add_Object(BULLET, pBullet);

		pBullet->Set_Pos(Get_Info().fX + 15.0, Get_Info().fY + 30.0);

		int iAngle = m_iAngle + (360 / m_iBulletCount) * i;
		pBullet->SetDir(Vector2D(cos(iAngle * PI / 180.f), sin(iAngle * PI / 180.f)));
	}

	m_iAngle = (m_iAngle + m_iAddAngle) % 360;
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
//				dynamic_cast<CBossBulletMulti*>(CObjMgr::GetInstance()->GetBack(BOSSBULLET))->SetDir(tor2D(1, 1));
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

