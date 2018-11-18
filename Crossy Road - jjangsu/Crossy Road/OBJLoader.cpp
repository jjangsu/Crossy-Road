#include "stdafx.h"
#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
	isLoadSuccess = false;
	rotate = 0.0;
	scaleFactor = 3;
	pos_x = 0.0;
	pos_y = -20.0;
	listIndex = glGenLists(1);
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::Open_ObjFile(string filepath)
{
	ifstream file;

	file.open(filepath.c_str(), ios::in);

	if (!file.is_open())
	{
		isLoadSuccess = false;

		cout << "File Load Failed" << endl;
		return;
	}

	faceCount = 0;
	vertexCount = 0;

	while (!file.eof())
	{
		getline(file, temp);
		if (temp[0] == 'v' && temp[1] == ' ')
			vertexCount++;
		else if (temp[0] == 'f' && temp[1] == ' ')
			faceCount++;
	}
	//cout << vertexCount << " " << faceCount << endl;

	//glPointSize(2.0);

	file.close();
	file.open(filepath.c_str(), ios::in);

	vertexs = new ObjStruct[vertexCount];
	faces = new FACES[faceCount * 3];
	faceCount = 0;
	vertexCount = 0;

	while (!file.eof())
	{
		getline(file, temp);
		if (temp.c_str()[0] == 'v' && temp.c_str()[1] == ' ')
		{
			temp[0] = ' ';
			sscanf_s(temp.c_str(), "%f %f %f"
				, &objStruct.x
				, &objStruct.y
				, &objStruct.z);

			//cout << "Draw Vertex3f : " << objStruct.x << " " << objStruct.y << " " << objStruct.z << endl;

			//glVertex3f(objStruct.x, objStruct.y, objStruct.z);

			vertexs[vertexCount] = objStruct;
			vertexCount++;

		}
		if (temp.c_str()[0] == 'f' && temp.c_str()[1] == ' ')
		{

			sscanf_s(temp.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&tempF[0].v, &tempF[0].vt, &tempF[0].vn,
				&tempF[1].v, &tempF[1].vt, &tempF[1].vn,
				&tempF[2].v, &tempF[2].vt, &tempF[2].vn);

			faces[faceCount] = tempF[0];
			faces[faceCount + 1] = tempF[1];
			faces[faceCount + 2] = tempF[2];
			faceCount += 3;
		}
	}

	isLoadSuccess = true;
}

void ObjLoader::draw()
{
	if (!isLoadSuccess)
	{
		return;
	}

	glPushMatrix();
	glTranslatef(pos_x, pos_y, -300);
	glColor3f(1.0, 1.0, 1.0);
	glScalef(scaleFactor, scaleFactor, scaleFactor);
	glRotatef(rotate, 0, 1, 0);

	//glCallList(listIndex);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faceCount / 12 * 12; ++i)
	{
		//glColor3f(float(i) / faceCount, float(i) / faceCount, float(i) / faceCount);
		glVertex3f(vertexs[faces[i].v - 1].x, vertexs[faces[i].v - 1].y, vertexs[faces[i].v - 1].z);
	}
	glEnd();

	glPopMatrix();
}

void ObjLoader::Rotate(GLfloat amount)
{
	rotate += amount;

	if (rotate < 0)
		rotate = 360;
	if (rotate > 360)
		rotate = 0;
}

void ObjLoader::Scale(GLfloat amount)
{
	scaleFactor += amount;
	if (scaleFactor < 1)
		scaleFactor = 1;
}

void ObjLoader::Move(GLfloat amntX, GLfloat amntY)
{
	pos_x += amntX;
	pos_y += amntY;
}