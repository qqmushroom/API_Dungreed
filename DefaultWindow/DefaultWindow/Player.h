#pragma once
#include "Obj.h"
#include "Weapon.h"
class CPlayer :	public CObj
{
public:
	enum	STATE { IDLE, RUN, RUN2, ATTACK, HIT, DEAD, ST_END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual  int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
	virtual void OnHit() override;

public:
	virtual void AddWeapon(CWeapon* pWeapon) 
	{
		m_vecWeapon.push_back(pWeapon);
	}

private:
	void		Key_Input();
	void		Jump();
	void        JumpEnd();
	/*void        UnderJump();*/
	void		Motion_Change();
	void		Offset();

	


	bool			m_bJump;		// 점프 상태 확인
	bool            m_bUnderJump;   // 밑 점프
	float			m_fJumpPower;	// 힘의 크기
	float			m_fTime;		// 점프 중 진행 시간 

	STATE			m_ePreState;
	STATE			m_eCurState;

	vector<CWeapon*>  m_vecWeapon;
	int m_iCurWeaponIndex = 0;
	//list<CObj*>	m_ObjList[END];
	};

