#include "stdafx.h"
#include "Scene.h"
#include "ObjMgr.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CScene::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CScene::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}


