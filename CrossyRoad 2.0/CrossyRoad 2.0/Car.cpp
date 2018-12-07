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
	speed = speed_;
}

Car::~Car()
{
}

void Car::move()
{
	position.x += direction * speed;
	if (position.x < -800 || position.x > 800) {
		speed = 0;
	}
}

void Car::setDir()
{
	if (position.x < 0)
		direction = 1;
	else
		direction = -1;
}
