#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"


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

}

void CScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}


