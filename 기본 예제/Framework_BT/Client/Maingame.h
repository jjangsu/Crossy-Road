#pragma once

class CObj;
class CMaingame
{
public:
	CMaingame();
	~CMaingame();

public:
	void Initialize();
	void Update(); // Progress
	void Render();
	void Release();

private:
	HDC m_hDC;

	CObj*		m_pPlayer;
	CObj*		m_pMonster;
	CObj*		m_pMouse;

	OBJLIST		m_BulletList;
};

