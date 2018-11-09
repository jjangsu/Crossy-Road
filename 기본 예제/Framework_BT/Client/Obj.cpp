#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_tInfo({}), m_tRect({})
{
}


CObj::~CObj()
{
}

void CObj::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX / 2);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY / 2);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX / 2);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY / 2);
}
