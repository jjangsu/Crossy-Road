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
		glTranslatef(position.x + 20.f, position.y, position.z);
		glScalef(40.f, 1.f, 1.f);
		glBegin(GL_QUADS);
		for (auto& iter : info)
		{
			glColor3f(iter.color.r, iter.color.g, iter.color.b);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
		}
		glEnd();
	}
	glPopMatrix();
}

void Tile::drawRail()
{

	glPushMatrix();
	{
		glTranslatef(position.x + 20.f, position.y, position.z);
		glScalef(16.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		for (auto& iter : info)
		{
			glColor3f(iter.color.r, iter.color.g, iter.color.b);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
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

		if (file)//읽는데 성공을 했다면
		{
			char buffer[300];
			int numofvertex;
			while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
			{
				fgets(buffer, 300, file);			// format
			}
			strcpy(buffer, buffer + strlen("element vertex"));
			sscanf(buffer, "%i", &numofvertex);

			while (strncmp("end_header", buffer, strlen("end_header")) != 0)
			{
				//system("pause");
				fgets(buffer, 300, file);//계속 입력을 받겠죠?
			}



			PLYINFO temp;
			for (int i = 0; i < numofvertex; ++i)
			{
				fgets(buffer, 300, file);
				sscanf(buffer, "%f %f %f %f %f %f", &temp.vec.x, &temp.vec.z, &temp.vec.y, &temp.color.r, &temp.color.g, &temp.color.b);
				temp.vec.x = -temp.vec.x;
				temp.vec.z = -temp.vec.z;
				// 왠지 모르겠지만 이렇게 해야지 저희 좌표계에서 정면 바라봐여
				temp.color.r = temp.color.r / 255.0;
				temp.color.g = temp.color.g / 255.0;
				temp.color.b = temp.color.b / 255.0;
				info.push_back(temp);
			}
		}
		else
		{
			std::cout << path.c_str() << "경로에서 파일을 찾는데 실패했습니다." << std::endl;
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

clock_t Tile::getCMake()
{
	return CarMake;
}

void Tile::setCMake(clock_t time)
{
	CarMake = time;
}

double Tile::getPeriod()
{
	return period;
}

void Tile::setPeriod(double cycle)
{
	period = cycle;
}

int Tile::getDirection()
{
	return direction;
}

void Tile::setDirection(int dir)
{
	direction = dir;
}

void Tile::setCarSpeed(float _speed)
{
	carSpeed = _speed;
}

float Tile::getCarSpeed()
{
	return carSpeed;
}

void Tile::setType(int t)
{
	type = t;
}

int Tile::getType()
{
	return type;
}
