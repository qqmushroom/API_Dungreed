#pragma once

#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
	
public:
	INFO		Get_Info() { return m_tInfo; }
	void		Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Direction(DIRECTION eDir) { m_eDir = eDir; }
	RECT		Get_Rect() { return m_tRect; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void		Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

	void		Set_PosX(float _fX) { m_tInfo.fX += _fX; }
	void		Set_PosY(float _fY) { m_tInfo.fY += _fY; }
	bool		Get_Dead() { return m_bDead; }
	void		Set_FrameKey(TCHAR* pFrameKey) { m_pFrameKey = pFrameKey; }

	int		Get_Hp() { return m_iHp; }
	int		Get_MaxHp() { return m_iMaxHp; }
public:
	virtual void Initialize()		PURE;
	virtual int  Update()			PURE;
	virtual void Late_Update()		PURE;
	virtual void Render(HDC hDC)	PURE;
	virtual void Release()			PURE;

	virtual void OnHit() {}
	virtual void Damaged(int _iValue);

	virtual void OnColiisionSphere(CObj* pCollisionObj) {}

protected:
	void		Update_Rect();
	void		Move_Frame();
	FRAME		m_tFrame;

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;

	float		m_fSpeed;
	float		m_fAngle;
	float		m_fDistance;

	bool		m_bDead;
	bool		m_bActive = false;

	CObj*		m_pTarget;
	TCHAR*		m_pFrameKey;

	int			m_iHp;
	int		    m_iMaxHp;
};

