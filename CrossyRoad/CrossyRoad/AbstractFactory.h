#pragma once

// �߻� ���丮 ����: (CObj ������) ��ü ���� �� ���ݵǴ� ����� ������ �߻�ȭ�ϴ� ������ ����.
// ��ü ������ ���� ���� ����(������ ����).

class Object; //���漱�� -> ���۸��غ��Ŷ�

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