#include "stdafx.h"
#include "ProgressBar.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

CProgressBar::CProgressBar()
{
}

CProgressBar::~CProgressBar()
{
}

void CProgressBar::Initialize()
{
    CSprite::Initialize();
}

int CProgressBar::Update()
{
    CSprite::Update();

	if (m_pTarget != nullptr)
	{
		m_fHpRatio = (float)m_pTarget->Get_Hp() / (float)m_pTarget->Get_MaxHp();
	}

    return OBJ_NOEVENT;
}

void CProgressBar::Late_Update()
{
    CSprite::Late_Update();
}

void CProgressBar::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX * m_fHpRatio,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX * m_fHpRatio, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달
}

void CProgressBar::Release()
{
    CSprite::Release();
}
