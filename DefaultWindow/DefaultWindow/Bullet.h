#pragma once
#include "obj.h"
#include "Vector2D.h"

class CBullet : public CObj
{
public:
	CBullet();
	virtual~CBullet();
public:
	virtual void Initialize()		override;
	virtual  int Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	void SetDir(Vector2D vecDir) { m_vecDir = vecDir; }

protected:
	Vector2D m_vecDir = Vector2D(0, 0);;
	float m_fSpeed = 0.f;

};