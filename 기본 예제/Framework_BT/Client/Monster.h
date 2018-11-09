#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

