#include "Obstacle.h"



Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

Obstacle::Obstacle(VECTOR3 vec, int _type)
{
	position = vec;
	type = _type;
}
