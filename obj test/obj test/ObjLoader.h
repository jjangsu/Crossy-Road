//
//  ObjLoader.h
//  OpenGL_Test
//
//  Created by NKS_Air on 13. 6. 7..
//  Copyright (c) 2013³â NKS_Air. All rights reserved.
//

#ifndef __OpenGL_Test__ObjLoader__
#define __OpenGL_Test__ObjLoader__

#include <gl/glut.h>
#include <iostream>
#include <fstream>
#include <string>

#endif /* defined(__OpenGL_Test__ObjLoader__) */

using namespace std;

typedef struct ObjStruct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}ObjStruct;

typedef struct __faces
{
	int v;
	int vt;
	int vn;
}FACES;

struct FACE
{
	ObjStruct _3vertex;
};

class ObjLoader {
private:
	bool isLoadSuccess;
	GLuint listIndex;
	GLfloat rotate;
	GLfloat scaleFactor;
	GLfloat pos_x;
	GLfloat pos_y;

	ObjStruct objStruct;
	FACES tempF[3];
	ObjStruct* vertexs;
	FACES* faces;
	string temp;
	int faceCount;
	int vertexCount;

public:
	ObjLoader();
	~ObjLoader();

	void Open_ObjFile(string filepath);
	void Create_Model();

	void Rotate(GLfloat amount);
	void Scale(GLfloat amount);
	void Move(GLfloat amntX, GLfloat amntY);
};