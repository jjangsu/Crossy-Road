#pragma once
#include "stdafx.h"

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
	void draw();

	void Rotate(GLfloat amount);
	void Scale(GLfloat amount);
	void Move(GLfloat amntX, GLfloat amntY);
};