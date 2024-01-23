#pragma once
#include "Obj.h"
class CWeapon : public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};
