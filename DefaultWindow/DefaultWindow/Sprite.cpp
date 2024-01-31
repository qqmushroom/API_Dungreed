#include "stdafx.h"
#include "Sprite.h"
#include "BmpMgr.h"

CSprite::CSprite()
{
}

CSprite::~CSprite()
{
}

void CSprite::Initialize()
{

}

int CSprite::Update()
{
    return OBJ_NOEVENT;
}

void CSprite::Late_Update()
{
	
}

void CSprite::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left,
		m_tRect.top,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달
}

void CSprite::Release()
{
	
}

void CSprite::SetImagePath(const TCHAR* _pFilePath, TCHAR* _pKey)
{
    CBmpMgr::Get_Instance()->InsertImage(_pFilePath, _pKey);

	m_pFrameKey = _pKey;
}

void CSprite::SetInfo(float _fX, float _fY, float _fCX, float _fCY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;

	CObj::Update_Rect();
}
