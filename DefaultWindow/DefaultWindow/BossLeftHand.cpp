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
#include "BossLeftHand.h"
#include "BossLeftLaser.h"

CBossLeftHand::CBossLeftHand() :
	m_ePreState(ST_END), m_eCurState(IDLE), m_iAngle(0)
{
}
CBossLeftHand::~CBossLeftHand()
{
}

void CBossLeftHand::Initialize()
{
	m_tInfo.fCX = 160.f;
	m_tInfo.fCY = 177.f;
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 515.f;
	m_iAngle = 0;

	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Character/Boss/BossLeftHandIdle.bmp", L"BossLeftHandIdle");

	m_pFrameKey = L"BossLeftHandIdle";

	m_tFrame = { 0, 9, 0, 600, GetTickCount() };

	m_vecMovePosition.emplace_back(Vector2D(250, 535));
	m_vecMovePosition.emplace_back(Vector2D(250, 355));
	m_vecMovePosition.emplace_back(Vector2D(250, 175));

	m_tInfo.fX = m_vecMovePosition[m_iCurrentPositionIndex].fX;
	m_tInfo.fY = m_vecMovePosition[m_iCurrentPositionIndex].fY;
}

int CBossLeftHand::Update()
{
	/*if (m_bDead)
		return OBJ_DEAD;*/

	// 2024.01.31 bskim: < 옆에 = 붙여서 딱 시간 맞았을때도 작동되게
	if (m_dwTime + 4000 <= GetTickCount())
	{

		BossLeftHand_Attack();

		m_dwTime = GetTickCount();
	}

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CBossLeftHand::Late_Update()
{
	Move_Frame();
	Motion_Change();
}

void CBossLeftHand::Render(HDC hDC)
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

void CBossLeftHand::Release()
{
}

void CBossLeftHand::Motion_Change()
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

void CBossLeftHand::BossLeftHand_Attack()
{
	/*CBullet* pBullet = new CBullet;
	pBullet->Initialize();
	CObjMgr::Get_Instance()->Add_Object(BULLET, pBullet);

	pBullet->Set_Pos(Get_Info().fX + 15.0, Get_Info().fY + 30.0);

	int iAngle = m_iAngle + (360 / m_iBulletCount);
	pBullet->SetDir(Vector2D(cos(iAngle * PI / 180.f), sin(iAngle * PI / 180.f)));*/

	vector<int> vecRand;
	for (int i = 0; i < m_vecMovePosition.size(); ++i)
	{
		if (i == m_iCurrentPositionIndex)
		{
			continue;
		}
		vecRand.emplace_back(i);
	}

	int iRand = rand() % vecRand.size();

	m_iCurrentPositionIndex = vecRand[iRand];

	m_tInfo.fX = m_vecMovePosition[m_iCurrentPositionIndex].fX;
	m_tInfo.fY = m_vecMovePosition[m_iCurrentPositionIndex].fY;

	CBossLeftLaser* pLaser = new CBossLeftLaser;
	if (pLaser != nullptr)
	{
		pLaser->Initialize();
		pLaser->Set_Pos(m_tInfo.fX, m_tInfo.fY);

		CObjMgr::Get_Instance()->Add_Object(LASER, pLaser);
	}
}
