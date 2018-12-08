#include "Car.h"
#include <iostream>

Car::Car()
{
	position = { 0, 0, 0 };
	direction = 1;
	speed = 0.5;
}

Car::Car(VECTOR3 vec, float speed_)
{
	position = vec;
	speed = speed_;
}

Car::Car(VECTOR3 vec)
{
	position = vec;
}

Car::~Car()
{
}

void Car::draw()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		glRotatef(90.0 * (direction +1), 0.0, 1.0 ,  0.0);
		glScalef(1.f, 1.f, 1.f);
		glBegin(GL_QUADS);
		for (auto& iter : info)
		{
			glColor3f(iter.color.r, iter.color.g, iter.color.b);
			glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
		}
		glEnd();
	}
	glPopMatrix();

}

void Car::move()
{
	position.x += direction * speed * frame.update();
}

void Car::setDir()
{
	if (position.x < 0)
		direction = 1;
	else
		direction = -1;
}

int Car::getDirection()
{
	return direction;
}

void Car::setSpeed(float _speed)
{
	speed = _speed;
}

float Car::getSpeed()
{
	return speed;
}

void Car::setWidth(int _width)
{
	width = _width;
}

int Car::getWidth()
{
	return width;
}
