#include "Object.h"

#include <iostream>

Object::Object()
{
	position = { 0,0,0 };
}

Object::Object(VECTOR3 vec)
{
	position = vec;
}


Object::~Object()
{
}

void Object::draw()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		glRotatef(angle.x, 1.0, 0.0, 0.0);
		glRotatef(angle.y, 0.0, 1.0, 0.0);
		glRotatef(angle.z, 0.0, 0.0, 1.0);
		//glScalef(1.f, 1.f, 1.f);
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

void Object::loadPLY(std::string path)
{
	char* exist = strstr((char*)path.c_str(), "ply");

	if (exist == NULL)
	{
		return;
	}

	else
	{
		FILE* file = fopen(path.c_str(), "r");

		if (file)//�дµ� ������ �ߴٸ�
		{
			std::cout << path.c_str() << std::endl;
			char buffer[300];
			int numofvertex;
			while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
			{
				fgets(buffer, 300, file);			// format
			}
			strcpy(buffer, buffer + strlen("element vertex"));
			sscanf(buffer, "%i", &numofvertex);

			std::cout << numofvertex << std::endl;

			while (strncmp("end_header", buffer, strlen("end_header")) != 0)
			{
				//system("pause");
				fgets(buffer, 300, file);//��� �Է��� �ް���?
			}



			PLYINFO temp;
			for (int i = 0; i < numofvertex; ++i)
			{
				fgets(buffer, 300, file);
				sscanf(buffer, "%f %f %f %f %f %f", &temp.vec.x, &temp.vec.z, &temp.vec.y, &temp.color.r, &temp.color.g, &temp.color.b);
				temp.vec.x = -temp.vec.x;
				temp.vec.z = -temp.vec.z;
				// ���� �𸣰����� �̷��� �ؾ��� ���� ��ǥ�迡�� ���� �ٶ����
				temp.color.r = temp.color.r / 255.0;
				temp.color.g = temp.color.g / 255.0;
				temp.color.b = temp.color.b / 255.0;
				info.push_back(temp);
			}

			std::cout << "-------------------------------------------------------------------------------------------" << std::endl;

		}
		else
		{
			std::cout << path.c_str() << "��ο��� ������ ã�µ� �����߽��ϴ�." << std::endl;
		}
	}
}

void Object::setPos(VECTOR3 vec)
{
	position = vec;
}

void Object::setRotation(VECTOR3 vec)
{
	angle = vec;
}

std::vector<PLYINFO> Object::getVector()
{
	return info;
}

void Object::setVector(std::vector<PLYINFO> vect)
{
	info = vect;
}

VECTOR3 Object::getPos()
{
	return position;
}

VECTOR3 Object::getSize()
{
	return size;
}

void Object::setSize(VECTOR3 _size)
{
	size = _size;
}
