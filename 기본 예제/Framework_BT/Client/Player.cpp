#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_tInfo = { 400.f, 400.f, 100.f, 100.f };
	m_fSpeed = 5.f;
}

int CPlayer::Update()
{
	// GetAsyncKeyState(VK_KEY): 해당 가상키가 눌렸는지 검사하는 함수.
	// 0x0000: 이전에 누른적 없고 호출시점에서도 누르지 않았을 때
	// 0x0001: 이전에 누른적 있고 호출시점에서 누르지 않았을 때
	// 0x8000: 이전에 누른적 없고 호출시점에서 눌렸을 때
	// 0x8001: 이전에 누른적 있고 호출시점에서 눌렸을 때

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_tInfo.fY -= m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_tInfo.fY += m_fSpeed;
	/*if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_pBulletList->push_back(CreateBullet());*/

	if (GetAsyncKeyState('W') & 0x8000)
		m_pBulletList->push_back(CreateBullet(DIR_UP));
	if (GetAsyncKeyState('S') & 0x8000)
		m_pBulletList->push_back(CreateBullet(DIR_DOWN));
	if (GetAsyncKeyState('A') & 0x8000)
		m_pBulletList->push_back(CreateBullet(DIR_LEFT));
	if (GetAsyncKeyState('D') & 0x8000)
		m_pBulletList->push_back(CreateBullet(DIR_RIGHT));

	return 0;
}

void CPlayer::Render(HDC hDC)
{
	UpdateRect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

CObj* CPlayer::CreateBullet()
{
	return CAbsractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
}

CObj* CPlayer::CreateBullet(DIRECTION eDir)
{
	CObj* pBullet = CAbsractFactory<CBullet>::CreateObj(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pBullet)->SetDir(eDir);

	return pBullet;
}