#pragma once
#include "Object.h"
class Obstacle :
	public Object
{
private: 

public:
	Obstacle();
	virtual ~Obstacle();

	Obstacle(VECTOR3 vec, int type);

	void setType(int _type);
	int getType();
	
};

