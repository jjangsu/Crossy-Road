#include "Car.h"
#include <iostream>


Car::Car()
{
	position = { 0, 0, 0 };
	direction = 1;
	speed = rand() % 5 + 3;
}

Car::Car(VECTOR3 vec, int speed_)
{
	position = vec;
	speed = speed_;
}

Car::~Car()
{
}

void Car::draw()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle.x, 1.0, 0.0, 0.0);
		glRotatef(angle.y, 0.0, 1.0, 0.0);
		glRotatef(angle.z, 0.0, 0.0, 1.0);
		glScalef(1.f, 1.f, 1.f);
		glBegin(GL_QUADS);
		for (auto& iter : info)
		{
			glColor3f(iter.color.r, iter.color.g, iter.color.b);
			glVertex3i(iter.vec.x, iter.vec.y, iter.vec.z);
		}
		glEnd();
	}
	glPopMatrix();

}

void Car::move()
{
	position.x += direction * speed;
	if (position.x < -800) 
		setPos({ +800,position.y,position.z });
	else if(position.x > 800)
		setPos({ -800,position.y,position.z });
}

void Car::setDir()
{
	if (position.x < 0)
		direction = 1;
	else
		direction = -1;
}
