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
};

