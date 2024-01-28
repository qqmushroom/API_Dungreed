#pragma once
#include "Boss.h"

class CBossLeftArm : public CBoss
{
public:
	CBossLeftArm();
	virtual ~CBossLeftArm();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void BossLeftArm_Attack();
};
