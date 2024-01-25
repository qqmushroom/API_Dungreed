#pragma once
#include "Obj.h"
class CPlayer;
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
public:
	virtual void AttachToPlayer(CPlayer* pPlayer);
	virtual void Attack() = 0;
 
    virtual RECT MakeAttackRect();

	bool GetIsAttack()
	{
		return m_bIsAttack;
	}

	

protected:
	CPlayer* m_pPlayerOwner = nullptr;

    INFO  m_tAttackStartInfo;
	DWORD m_dwAttackTime = 0;
	DWORD m_dwAttackStartTime = 0;
	bool  m_bIsAttack = false;
};
