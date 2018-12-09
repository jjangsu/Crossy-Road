#pragma once
#include "Object.h"
#include "Define.h"

class Character : public Object
{

private:
	int jumpstate = 0;
	VECTOR3 targetVertex = {};

public:
	Character();
	Character(VECTOR3);
	~Character();

	void jump(int key);
};
