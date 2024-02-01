#pragma once
#include "Obj.h"

class CBoss : public CObj
{
public:
	enum	STATE { IDLE, ST_END };
public:
	CBoss();
	virtual~CBoss();

public:
	virtual void Initialize()     override;
	virtual int  Update()         override;
	virtual void Late_Update()    override;
	virtual void Render(HDC hDC)  override;
	virtual void Release()        override;

private:
	void		Motion_Change();
	void        Boss_Attack();

	void Take_Damage(int _iDamage);

	STATE		m_ePreState;
	STATE		m_eCurState;

protected:
	int         m_iAngle;
	int         m_iAddAngle;
	int         m_iBulletCount;

	DWORD		m_dwTime;
};
