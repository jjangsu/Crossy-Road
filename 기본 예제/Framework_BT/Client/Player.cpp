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
	// GetAsyncKeyState(VK_KEY): �ش� ����Ű�� ���ȴ��� �˻��ϴ� �Լ�.
	// 0x0000: ������ ������ ���� ȣ����������� ������ �ʾ��� ��
	// 0x0001: ������ ������ �ְ� ȣ��������� ������ �ʾ��� ��
	// 0x8000: ������ ������ ���� ȣ��������� ������ ��
	// 0x8001: ������ ������ �ְ� ȣ��������� ������ ��

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