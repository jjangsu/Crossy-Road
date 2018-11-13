#pragma once
#include "Vector.h"

class Object
{
protected:
	//필요한 변수 있으면 추가하자고
	VECTOR info;
	float speed;

	// void updateObject(); //나중에 필요하면 만들자

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

