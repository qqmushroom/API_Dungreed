#pragma once

#include "Obj.h"

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void		Add_Object(OBJID eID, CObj* pObj);
	void		Delete_Object(OBJID _eID);
	int			Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();

	void		Delete_ID(OBJID eID);

public:
	CObj*		Get_Target(OBJID eID, CObj* pObj);

public:

	list<CObj*>*	GetList(OBJID _eID) { return &m_ObjList[_eID]; }
	CObj*			GetBack(OBJID _eID) { return m_ObjList[_eID].back(); }

	static CObjMgr*		Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}


private:
	list<CObj*>		m_ObjList[END];
	static CObjMgr*	m_pInstance;

};
