#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

CKeyMgr::CKeyMgr()
{
	ZeroMemory(m_KeyState, sizeof(m_KeyState));
}

CKeyMgr::~CKeyMgr()
{
}

bool CKeyMgr::Key_Down(int _iKey)
{
	if (!m_KeyState[_iKey] && (GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_KeyState[_iKey] = !m_KeyState[_iKey];
		return true;
	}

	for (size_t i = 0; i < VK_MAX; ++i)
	{
		if (m_KeyState[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_KeyState[i] = !m_KeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_Up(int _iKey)
{
	if (m_KeyState[_iKey] && !(GetAsyncKeyState(_iKey) & 0x8000))
	{
		m_KeyState[_iKey] = !m_KeyState[_iKey];
		return true;
	}

	for (size_t i = 0; i < VK_MAX; ++i)
	{
		if (!m_KeyState[i] && (GetAsyncKeyState(i) & 0x8000))
			m_KeyState[i] = !m_KeyState[i];
	}

	return false;
}

bool CKeyMgr::Key_Pressing(int _iKey)
{
	if (GetAsyncKeyState(_iKey) & 0x8000)
		return true;

	return false;
}
