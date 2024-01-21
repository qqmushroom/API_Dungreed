#pragma once
#include "Obj.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		Key_Input();
	void		Jump();


	bool			m_bJump;		// 점프 상태 확인	
	float			m_fJumpPower;	// 힘의 크기
	float			m_fTime;		// 점프 중 진행 시간 
};

