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

	// GetCursorPos: ��ü ��ũ�� ���� �󿡼��� ���콺 ��ǥ�� ���´�!
	GetCursorPos(&pt);

	// ScreenToClient: ���� ��ũ�� ������ ��ǥ�� ���� Ŭ���̾�Ʈ ���� ��ǥ�� ��ȯ���ִ� �Լ�!
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
