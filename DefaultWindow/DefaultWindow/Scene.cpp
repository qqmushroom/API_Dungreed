#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "Obj.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Update()
{
	CObjMgr::Get_Instance()->Update();
	CCollisionMgr::Collision_RectEx(*CObjMgr::Get_Instance()->GetList(PLAYER), *CObjMgr::Get_Instance()->GetList(FLOOR));

	//플레이어와 보스총알 충돌처리
	list<CObj*>* pPlayerList = CObjMgr::Get_Instance()->GetList(PLAYER);
	list<CObj*>* pBulletList = CObjMgr::Get_Instance()->GetList(BULLET);

	CObj* pPlayer(nullptr);
	CObj* pBullet(nullptr);
	if (CCollisionMgr::Get_Instance()->Collision_Spheres(*pPlayerList, *pBulletList, pPlayer, pBullet))
	{
		
		pBullet->Set_Dead();
		pPlayer->Damaged(1);
	}


}

void CScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CScene::Release()
{
	CObjMgr::Get_Instance()->Delete_ID(BULLET);
}


