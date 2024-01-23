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
	// void	Set_Weapon(list<CObj*>* pWeapon) { m_pWeapon = pWeapon; } 

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
	//void        Player_Attack();
	


	bool			m_bJump;		// ���� ���� Ȯ��
	bool            m_bUnderJump;   // �� ����
	float			m_fJumpPower;	// ���� ũ��
	float			m_fTime;		// ���� �� ���� �ð� 

	STATE			m_ePreState;
	STATE			m_eCurState;

	//list<CObj*>*	m_pWeapon;
	//list<CObj*>	m_ObjList[END];
	};

