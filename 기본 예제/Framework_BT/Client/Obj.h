#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	const INFO& GetInfo() { return m_tInfo; }

public:
	void SetPos(float fX, float fY) { m_tInfo.fX = fX, m_tInfo.fY = fY; }

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

protected:
	void UpdateRect();

protected:
	INFO	m_tInfo;
	RECT	m_tRect;
	float	m_fSpeed;
};

