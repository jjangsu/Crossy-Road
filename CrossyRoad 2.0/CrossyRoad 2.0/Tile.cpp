#include "Tile.h"


Tile::Tile()
{
	position = { 0,0,0 };
}

Tile::Tile(VECTOR3 vec)
{
	position = vec;
}


Tile::~Tile()
{
}

void Tile::draw()
{
	glPushMatrix();
	{
		glTranslatef(position.x + 20, position.y, position.z);
		glScalef(40.f, 1.f, 1.f);
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

void Tile::loadPLY(std::string path)
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
				sscanf(buffer, "%d %d %d %f %f %f", &temp.vec.x, &temp.vec.z, &temp.vec.y, &temp.color.r, &temp.color.g, &temp.color.b);
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

void Tile::setPos(VECTOR3 vec)
{
	position = vec;
}

void Tile::setRotation(VECTOR3 vec)
{
	angle = vec;
}

std::vector<PLYINFO> Tile::getVector()
{
	return info;
}

void Tile::setVector(std::vector<PLYINFO> vect)
{
	info = vect;
}
