#pragma once

// �߻� ���丮 ����: (CObj ������) ��ü ���� �� ���ݵǴ� ����� ������ �߻�ȭ�ϴ� ������ ����.
// ��ü ������ ���� ���� ����(������ ����).


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