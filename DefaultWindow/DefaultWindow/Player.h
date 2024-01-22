#pragma once
#include "Obj.h"
class CPlayer :	public CObj
{
public:
	enum	STATE { IDLE, RUN, RUN2, ATTACK, HIT, DEAD, ST_END };

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
	void        UnderJump();
	void		Motion_Change();


	bool			m_bJump;		// 점프 상태 확인
	bool            m_bUnderJump;   // 밑 점프
	float			m_fJumpPower;	// 힘의 크기
	float			m_fTime;		// 점프 중 진행 시간 

	STATE			m_ePreState;
	STATE			m_eCurState;
};

