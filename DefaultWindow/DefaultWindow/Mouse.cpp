#include "stdafx.h"
#include "Mouse.h"
#include "BmpMgr.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 63.f;
	m_tInfo.fCY = 63.f;
	CBmpMgr::Get_Instance()->InsertImage(L"../Image/Ui/ShootingCursor.bmp", L"ShootingCursor");

	m_pFrameKey = L"ShootingCursor";

	m_tFrame = { 0, 0, 0, 200, GetTickCount() };
}

int CMouse::Update()
{
	POINT	ptMouse{};

	GetCursorPos(&ptMouse);

	// 전체 스크린 영역에서 클라이언트 좌표로 변환
	ScreenToClient(g_hWnd, &ptMouse);

	m_tInfo.fX = (float)ptMouse.x;
	m_tInfo.fY = (float)ptMouse.y;

	__super::Update_Rect();

	ShowCursor(false);	// 마우스 커서의 출력 유무를 결정

	return OBJ_NOEVENT;

}

void CMouse::Late_Update()
{
}

void CMouse::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Get_Image(m_pFrameKey);

	GdiTransparentBlt(hDC,
		m_tRect.left, //+ iScrollX,
		m_tRect.top, //+ iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		m_tFrame.iFrameStart * (int)m_tInfo.fCX,
		m_tFrame.iMotion * (int)m_tInfo.fCY,
		(int)m_tInfo.fCX, // 복사할 비트맵의 가로, 세로 길이
		(int)m_tInfo.fCY,
		RGB(255, 0, 255));	// 제거하고자 하는 색상을 전달
}

void CMouse::Release()
{
}
 