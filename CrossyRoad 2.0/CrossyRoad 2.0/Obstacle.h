#pragma once
#include <GL/freeglut.h>
#include "Define.h"
#include "Object.h"


class Obstacle : public Object
{
private: 
	int type;
public:
	Obstacle();
	virtual ~Obstacle();

	Obstacle(VECTOR3 vec, int type);

	void setType(int _type);
	int getType();

	void draw();
	
};

