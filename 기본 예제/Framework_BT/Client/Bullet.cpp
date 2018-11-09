#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDir(DIR_UP)
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 10.f;
}

int CBullet::Update()
{
	switch (m_eDir)
	{
	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	}

	if (100.f >= m_tInfo.fX || 100.f >= m_tInfo.fY || WINCX - 100 <= m_tInfo.fX || WINCY - 100 <= m_tInfo.fY)
		return 1;

	return 0;
}

void CBullet::Render(HDC hDC)
{
	UpdateRect();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}
