#pragma once
#include "BossSprite.h"
class CBossProgressBar :
	public CBossSprite
{
public:
	CBossProgressBar();
	virtual ~CBossProgressBar();

public:
	virtual void Initialize()     override;
	virtual int  Update()         override;
	virtual void Late_Update()    override;
	virtual void Render(HDC hDC)  override;
	virtual void Release()        override;

public:
	virtual void SetTarget(CObj* pTarget) { m_pTarget = pTarget; }

protected:
	float m_fHpRatio = 5;
	CObj* m_pTarget = nullptr;
};
