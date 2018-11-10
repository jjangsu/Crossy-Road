//
//  ObjLoader.cpp
//  OpenGL_Test
//
//  Created by NKS_Air on 13. 6. 7..
//  Copyright (c) 2013³â NKS_Air. All rights reserved.
//

#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
	isLoadSuccess = false;
	rotate = 0.0;
	scaleFactor = 10;
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

	ObjStruct objStruct;
	string temp;

	glPointSize(2.0);
	glNewList(listIndex, GL_COMPILE_AND_EXECUTE);// GL_COMPILE);
	glPushMatrix();
	glBegin(GL_POINTS);

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

			cout << "Draw Vertex3f : " << objStruct.x << " " << objStruct.y << " " << objStruct.z << endl;

			glVertex3f(objStruct.x, objStruct.y, objStruct.z);
		}
	}

	glEnd();
	glPopMatrix();
	glEndList();

	isLoadSuccess = true;
}

void ObjLoader::Create_Model()
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

	glCallList(listIndex);

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