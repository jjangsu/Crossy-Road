#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Mouse.h"


CMaingame::CMaingame()
	: m_pPlayer(nullptr), m_pMonster(nullptr), m_pMouse(nullptr)
{
}


CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Initialize()
{
	// GetDC: DC할당 함수.
	m_hDC = GetDC(g_hWnd);

	if (nullptr == m_pPlayer)
	{
		m_pPlayer = CAbsractFactory<CPlayer>::CreateObj();
		dynamic_cast<CPlayer*>(m_pPlayer)->SetBulletList(&m_BulletList);
	}

	if (nullptr == m_pMonster)
		m_pMonster = CAbsractFactory<CMonster>::CreateObj();

	if (nullptr == m_pMouse)
		m_pMouse = CAbsractFactory<CMouse>::CreateObj();
}

void CMaingame::Update()
{
	m_pPlayer->Update();
	m_pMonster->Update();
	m_pMouse->Update();

	OBJITER iter_begin = m_BulletList.begin();
	OBJITER iter_end = m_BulletList.end();

	for (; iter_begin != iter_end; )
	{
		int iEvent = (*iter_begin)->Update();

		if (1 == iEvent)
		{
			SafeDelete(*iter_begin);
			iter_begin = m_BulletList.erase(iter_begin);
		}
		else
			++iter_begin;
	}
}

void CMaingame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	Rectangle(m_hDC, 100, 100, WINCX - 100, WINCY - 100);

	m_pPlayer->Render(m_hDC);
	m_pMonster->Render(m_hDC);
	m_pMouse->Render(m_hDC);

	OBJITER iter_begin = m_BulletList.begin();
	OBJITER iter_end = m_BulletList.end();

	for (; iter_begin != iter_end; ++iter_begin)
		(*iter_begin)->Render(m_hDC);

	TCHAR szBuf[32] = L"";
	swprintf_s(szBuf, L"Bullet: %d", m_BulletList.size());

	// SetWindowText: 해당 윈도우의 타이틀바에 문자열을 출력하는 함수
	SetWindowText(g_hWnd, szBuf);

	// 현재 DC에 문자열을 출력하는 함수
	//TextOut(m_hDC, 50, 50, szBuf, lstrlen(szBuf));
}

void CMaingame::Release()
{
	// DC 해제
	ReleaseDC(g_hWnd, m_hDC);

	SafeDelete(m_pPlayer);
	SafeDelete(m_pMonster);
	SafeDelete(m_pMouse);
	
	for_each(m_BulletList.begin(), m_BulletList.end(), SafeDelete<CObj*>);
}
