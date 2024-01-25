#pragma once

#define WINCX		800
#define WINCY		600

#define PURE		= 0

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1

#define VK_MAX			0xff

#define KEY_DOWN(key)	CKeyMgr::GetInstance()->Key_Down(key)
#define KEY_UP(key)		CKeyMgr::GetInstance()->Key_Up(key)
#define KEY_PRESS(key)	CKeyMgr::GetInstance()->Key_Pressing(key)

#define PI				(3.14f)
#define GRAVITY			(9.8f)
template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iMotion;
	DWORD	dwSpeed;
	DWORD	dwTime;

}FRAME;

typedef struct tagLingPoint
{
	float	fX;
	float	fY;

	tagLingPoint() { ZeroMemory(this, sizeof(tagLingPoint)); }
	tagLingPoint(float _fX, float _fY) : fX(_fX), fY(_fY) { }

}LINEPOINT;

typedef struct tagLine
{
	LINEPOINT	tLeft;
	LINEPOINT	tRight;

	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT& _tLeft, LINEPOINT& _tRight)
		: tLeft(_tLeft), tRight(_tRight) {}

}LINE;


enum	OBJID
{
	PLAYER,
	MOUSE,
	WEAPON,
	END
};

enum SCENEID
{
	STAGE_1,
	STAGE_2,
	STAGE_END
};
enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,
	DIR_END
};

struct tagFinder
{
public:
	tagFinder(const TCHAR* pString) : m_pString(pString) {}

public:
	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(m_pString, Pair.first);
	}

private:
	const TCHAR*		m_pString;
};


extern HWND g_hWnd;