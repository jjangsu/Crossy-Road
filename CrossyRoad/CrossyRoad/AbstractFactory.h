#pragma once

// 추상 팩토리 패턴: (CObj 하위의) 객체 생성 시 수반되는 공통된 로직을 추상화하는 디자인 패턴.
// 객체 생성에 대한 설계 구조(디자인 패턴).

class Object; //전방선언 -> 구글링해보거라

template <typename T>
class AbsractFactory
{
public:
	static MainGame* CreateObject()
	{
		Object* obj = new T;
		obj->Initialisze();
		return obj;
	}

	static Object* CreateObj(float x, float y, float z)
	{
		Object* obj = new T;
		obj->Initialisze();
		obj->setPos(x, y, z);
		return obj;
	}
};