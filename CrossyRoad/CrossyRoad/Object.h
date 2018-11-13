#pragma once
#include "Vector.h"

class Object
{
protected:
	//�ʿ��� ���� ������ �߰����ڰ�
	VECTOR info;
	float speed;

	// void updateObject(); //���߿� �ʿ��ϸ� ������

public:
	Object();
	virtual ~Object();

	const VECTOR& getInfo()
	{
		return info;
	}

	virtual void initialize() =0;
	virtual int update() = 0;
	virtual void render() = 0;

	void setPos(float x, float y, float z)
	{
		info.x = x;
		info.y = y;
		info.z = z;
	}




};

