#pragma once

// 추상 팩토리 패턴: (CObj 하위의) 객체 생성 시 수반되는 공통된 로직을 추상화하는 디자인 패턴.
// 객체 생성에 대한 설계 구조(디자인 패턴).


class CObj;

template <typename T>
class CAbsractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* CreateObj(float fX, float fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->SetPos(fX, fY);

		return pObj;
	}
};