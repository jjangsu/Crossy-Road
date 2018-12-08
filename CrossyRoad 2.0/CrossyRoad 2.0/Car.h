#pragma once

#include "Object.h"
#include "Time.h"

class Car : public Object
{
private:
	int direction;
	float speed;
	int width;

	Time frame;
public:
	Car();
	Car(VECTOR3 vec, float speed_);
	Car(VECTOR3 vec);
	
	~Car();

	void draw();
	void move();
	void setDir();

	int getDirection();
	void setSpeed(float _speed);
	float getSpeed();
	void setWidth(int _width);
	int getWidth();
};

