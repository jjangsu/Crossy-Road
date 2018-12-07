#include "Car.h"


Car::Car()
{
	position = { 0, 0, 0 };
}

Car::Car(VECTOR3 vec)
{
	position = vec;
}

Car::~Car()
{
}
