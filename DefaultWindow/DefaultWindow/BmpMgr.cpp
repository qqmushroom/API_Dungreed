#include "stdafx.h"
#include "BmpMgr.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;

CBmpMgr::CBmpMgr()
{
}

CBmpMgr::~CBmpMgr()
{
    Release();
}

void CBmpMgr::InsertImage(const TCHAR* _pFilePath, const TCHAR* _pKey)
{
    auto    iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](const pair<const TCHAR*, CMyBmp*>& Pair)->bool
        {
            return !lstrcmp(Pair.first, _pKey);
        }
    );

    if (iter == m_mapBit.end())
    {
        CMyBmp* Temp = new CMyBmp;
        Temp->LoadBmp(_pFilePath);

        m_mapBit.insert({ _pKey, Temp });
    }
}

HDC CBmpMgr::Get_Image(const TCHAR* _pKey)
{
    auto    iter = find_if(m_mapBit.begin(), m_mapBit.end(), [&](const pair<const TCHAR*, CMyBmp*>& Pair)->bool
        {
            return !lstrcmp(Pair.first, _pKey);
        }
    );

    if (iter == m_mapBit.end())
        return nullptr;

    return (iter->second)->Get_MemDC();
}

void CBmpMgr::Release()
{
    for_each(m_mapBit.begin(), m_mapBit.end(), [](auto& Pair)
        {
            if (Pair.second)
            {
                delete Pair.second;
                Pair.second = nullptr;
            }
        }
    );

    m_mapBit.clear();
}
