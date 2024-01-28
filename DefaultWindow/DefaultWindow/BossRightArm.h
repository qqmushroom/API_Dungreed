#pragma once
#include "Boss.h"

class CBossRightArm : public CBoss
{
public:
	CBossRightArm();
	virtual ~CBossRightArm();

public:
	virtual void Initialize() override;
	virtual int  Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void BossRightArm_Attack();
};