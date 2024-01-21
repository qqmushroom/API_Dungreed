#pragma once

#include "Define.h"
#include "MyBmp.h"

class CBmpMgr
{
private:
	CBmpMgr();
	~CBmpMgr();

public:
	void		InsertImage(const TCHAR* _pFilePath, const TCHAR* _pKey);
	HDC			Get_Image(const TCHAR* _pKey);
	void		Release();

public:
	static CBmpMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CBmpMgr;

		return m_pInstance;
	}

	static void		DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CBmpMgr*				m_pInstance;
	map<const TCHAR*, CMyBmp*>	m_mapBit;
};