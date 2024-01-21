#include "stdafx.h"
#include "MyBmp.h"

CMyBmp::CMyBmp()
	: m_hMemDC(nullptr), m_hBitmap(nullptr), m_hOldBmp(nullptr)
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::LoadBmp(const TCHAR* _pFilePath)
{
	HDC		hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(nullptr, _pFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
