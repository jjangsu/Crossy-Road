#pragma once
#include "Object.h"

class Car : public Object
{
private:
	int direction;
	int speed;
	int width;
public:
	Car();
	Car(VECTOR3 vec, int speed_);
	Car(VECTOR3 vec);
	
	~Car();

	void draw();
	void move();
	void setDir();

	int getDirection();
	void setSpeed(int _speed);
	void setWidth(int _width);
	int getWidth();
};

