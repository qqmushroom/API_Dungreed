#pragma once

#include "Obj.h"

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void		Collision_Rect(list<CObj*> Dst, list<CObj*> Src);
	static void		Collision_Sphere(list<CObj*> Dst, list<CObj*> Src);
	static bool		Check_Sphere(CObj* pDst, CObj* pSrc);

	static void		Collision_RectEx(list<CObj*> Dst, list<CObj*> Src);
	static bool		Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float *pY);
	static bool		Collision_Spheres(list<CObj*> _Dest, list<CObj*> _Sour, CObj*& _ColDst, CObj*& _ColSrc);
public:
	static CCollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CCollisionMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CCollisionMgr* m_pInstance;
};

