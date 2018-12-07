#pragma once
#include "Character.h"
class Car : public Character
{
private:
	int direction;
	int speed;
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
};

