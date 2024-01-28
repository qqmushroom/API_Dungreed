#pragma once

#include "Obj.h"

class CBox : public CObj
{
public:
	CBox();
	CBox(float _fX, float _fY, float _fCX, float _fCY);
	~CBox();

	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	virtual void SetPos(float _fX, float _fY);
};