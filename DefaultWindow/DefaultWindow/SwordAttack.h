#pragma once
#include "Obj.h"
class CSwordAttack :
    public CObj
{
	enum eAttackDir
	{
		ATTACK_DIR_UP,
		ATTACK_DIR_RIGHT_UP,
		ATTACK_DIR_RIGHT,
		ATTACK_DIR_RIGHT_DOWN,
		ATTACK_DIR_DOWN,
		ATTACK_DIR_LEFT_DOWN,
		ATTACK_DIR_LEFT,
		ATTACK_DIR_LEFT_UP,
		ATTACK_DIR_END
	};
public:
	CSwordAttack();
	virtual ~CSwordAttack();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void SetAttackDir(Vector2D vDir);

protected:
	DWORD m_dwAttackTime = 0;
	DWORD m_dwAttackStartTime = 0;
};

