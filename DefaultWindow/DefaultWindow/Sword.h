#pragma once
#include "weapon.h"
class CSword : public CWeapon
{
public:
	CSword();
	virtual ~CSword();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	virtual void Attack() override;
};