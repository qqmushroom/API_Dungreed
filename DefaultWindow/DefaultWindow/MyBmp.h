#pragma once
#include <map>
#include "Define.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

	void		LoadBmp(const TCHAR* _pFilePath);
	void		Release();

public:
	HDC			Get_MemDC() { return m_hMemDC; }

private:
	HDC			m_hMemDC;
	
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBmp;
};