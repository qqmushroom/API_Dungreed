#pragma once
#include "obj.h"
#include "Vector2D.h"

class CBossRightLaser : public CObj
{
public:
	CBossRightLaser();
	virtual~CBossRightLaser();
public:
	virtual void Initialize()		override;
	virtual  int Update()			override;
	virtual void Late_Update()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

	void    Update_Rect();

protected:
	DWORD   m_dwTIME;
	TCHAR*  m_pHeadFrameKey;
	RECT    m_tHeadRect;
	INFO    m_tHeadInfo;
	FRAME   m_tHeadFrame;

	void	Move_HeadFrame();

	int     m_iBodyCount = 0;
};