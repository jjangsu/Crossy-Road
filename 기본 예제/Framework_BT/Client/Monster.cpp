#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo = { 400.f, 200.f, 100.f, 100.f };
	m_fSpeed = 3.f;
}

int CMonster::Update()
{
	m_tInfo.fX += m_fSpeed;

	UpdateRect();

	if (WINCX - 100 <= m_tRect.right)
		m_fSpeed *= -1.f;
	else if (100 >= m_tRect.left)
		m_fSpeed *= -1.f;

	return 0;
}

void CMonster::Render(HDC hDC)
{
	UpdateRect();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release()
{
}
