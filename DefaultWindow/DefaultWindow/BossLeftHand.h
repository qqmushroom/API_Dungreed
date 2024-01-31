#pragma once
#include "Obj.h"

class CBossLeftHand : public CObj
{
public:
	enum	STATE { IDLE, ST_END };
public:
	CBossLeftHand();
	virtual~CBossLeftHand();

public:
	virtual void Initialize()     override;
	virtual int  Update()         override;
	virtual void Late_Update()    override;
	virtual void Render(HDC hDC)  override;
	virtual void Release()        override;

private:
	void		Motion_Change();
	void        BossLeftHand_Attack();

	STATE		m_ePreState;
	STATE		m_eCurState;

protected:
	int         m_iAngle;

	DWORD		m_dwTime;
};
