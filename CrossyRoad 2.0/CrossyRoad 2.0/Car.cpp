#include "Car.h"
#include <iostream>


Car::Car()
{
	position = { 0, 0, 0 };
	direction = 1;
	speed = 5;
}

Car::Car(VECTOR3 vec, int speed_)
{
	position = vec;
	direction = -1;
	speed = speed_;
}

Car::~Car()
{
}

void Car::move()
{
	position.x += direction * speed;
	if (position.x < -800) {
		setPos({ +800,position.y,position.z });
	}
}
