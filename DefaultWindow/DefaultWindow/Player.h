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


	bool			m_bJump;		// ���� ���� Ȯ��	
	float			m_fJumpPower;	// ���� ũ��
	float			m_fTime;		// ���� �� ���� �ð� 
};

