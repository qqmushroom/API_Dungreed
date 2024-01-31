#pragma once
#include "Sprite.h"
class CProgressBar :
    public CSprite
{
public:
	CProgressBar();
	virtual ~CProgressBar();

public:
	virtual void Initialize()     override;
	virtual int  Update()         override;
	virtual void Late_Update()    override;
	virtual void Render(HDC hDC)  override;
	virtual void Release()        override;

public:
	virtual void SetTarget(CObj* pTarget) { m_pTarget = pTarget; }

protected:
	float m_fHpRatio = 1;
	CObj* m_pTarget = nullptr;
};

