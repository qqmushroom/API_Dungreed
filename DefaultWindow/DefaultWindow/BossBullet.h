#pragma once
class CBossBullet : 
{
public:
	CMonsterBullet1();
	virtual~CMonsterBullet1();
public:
	virtual void Initialize()		override;
	virtual  int Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC hDC)	override;
	virtual void Release()			override;

};
