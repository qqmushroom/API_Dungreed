#pragma once
#include "Obj.h"
class CSprite :
    public CObj
{
public:
    CSprite();
    virtual ~CSprite();

public:
	virtual void Initialize()     override;
	virtual int  Update()         override;
	virtual void Late_Update()    override;
	virtual void Render(HDC hDC)  override;
	virtual void Release()        override;

public:
	virtual void SetImagePath(const TCHAR* _pFilePath, TCHAR* _pKey);
	virtual void SetInfo(float _fX, float _fY, float _fCX, float _fCY);
};

