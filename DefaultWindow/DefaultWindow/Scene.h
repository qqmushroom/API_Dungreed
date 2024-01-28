#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void	Initialize()PURE;
	virtual void	Update();
	virtual void	Late_Update();
	virtual void	Render(HDC hDC);
	virtual void	Release()PURE;

};
