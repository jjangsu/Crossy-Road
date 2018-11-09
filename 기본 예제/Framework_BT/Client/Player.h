#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetBulletList(OBJLIST* pBulletList) { m_pBulletList = pBulletList;	}

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CObj* CreateBullet();
	CObj* CreateBullet(DIRECTION eDir);

private:
	OBJLIST* m_pBulletList;
};

