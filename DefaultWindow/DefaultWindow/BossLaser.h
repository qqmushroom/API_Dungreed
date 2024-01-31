#pragma once
#include "obj.h"
#include "Vector2D.h"

class CBossLaser : public CObj
{
public:
	enum	STATE { HEAD1, HEAD2, BODY1, BODY2, ST_END };
public:
	CBossLaser();
	virtual~CBossLaser();
public:
	virtual void Initialize()		override;
	virtual  int Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	void SetDir(Vector2D vecDir) { m_vecDir = vecDir; }

private:
	void Motion_Change();

	STATE		m_ePreState;
	STATE		m_eCurState;
protected:
	Vector2D m_vecDir = Vector2D(0, 0);;
	float m_fSpeed = 0.f;

};