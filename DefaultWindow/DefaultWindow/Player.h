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

	


	bool			m_bJump;		// ���� ���� Ȯ��
	bool            m_bUnderJump;   // �� ����
	float			m_fJumpPower;	// ���� ũ��
	float			m_fTime;		// ���� �� ���� �ð� 

	STATE			m_ePreState;
	STATE			m_eCurState;

	vector<CWeapon*>  m_vecWeapon;
	int m_iCurWeaponIndex = 0;
	//list<CObj*>	m_ObjList[END];
	};

