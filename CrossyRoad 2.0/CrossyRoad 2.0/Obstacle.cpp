#include "Obstacle.h"

extern std::vector<PLYINFO> usingBigTreeVector;
extern std::vector<PLYINFO> usingSmallTreeVector;
extern std::vector<PLYINFO> usingBigStoneVector;
extern std::vector<PLYINFO> usingSmallStoneVector;

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

void Obstacle::setType(int _type)
{
	type = _type;
}

int Obstacle::getType()
{
	return type;
}

void Obstacle::draw()
{
	glPushMatrix();
	{
		glTranslatef(position.x, position.y, position.z);
		if (type == BIGTREE)
		{
			glBegin(GL_QUADS);
			for (auto& iter : usingBigTreeVector)
			{
				glColor3f(iter.color.r, iter.color.g, iter.color.b);
				glNormal3f(0.0, 1.0, 0.0);
				glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
			}
			glEnd();
		}

		else if (type == SMALLTREE)
		{
			glBegin(GL_QUADS);
			for (auto& iter : usingSmallTreeVector)
			{
				glColor3f(iter.color.r, iter.color.g, iter.color.b);
				glNormal3f(0.0, 1.0, 0.0);
				glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
			}
			glEnd();
		}
		else if (type == SMALLSTONE)
		{
			glBegin(GL_QUADS);
			for (auto& iter : usingSmallStoneVector)
			{
				glColor3f(iter.color.r, iter.color.g, iter.color.b);
				glNormal3f(0.0, 1.0, 0.0);
				glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
			}
			glEnd();
		}

		if (type == BIGSTONE)
		{
			glBegin(GL_QUADS);
			for (auto& iter : usingBigStoneVector)
			{
				glColor3f(iter.color.r, iter.color.g, iter.color.b);
				glNormal3f(0.0, 1.0, 0.0);
				glVertex3f(iter.vec.x, iter.vec.y, iter.vec.z);
			}
			glEnd();
		}
	}
	glPopMatrix();
}
