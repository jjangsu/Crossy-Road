#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMouse::Update()
{
	POINT pt;

	// GetCursorPos: 전체 스크린 영역 상에서의 마우스 좌표를 얻어온다!
	GetCursorPos(&pt);

	// ScreenToClient: 얻어온 스크린 영역의 좌표를 현재 클라이언트 상의 좌표로 변환해주는 함수!
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;

	return 0;
}

void CMouse::Render(HDC hDC)
{
	UpdateRect();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMouse::Release()
{
}
