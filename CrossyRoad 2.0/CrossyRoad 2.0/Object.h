#pragma once
#include <vector>
#include <gl/freeglut.h>
#include "Struct.h"

class Object
{
protected:
	std::vector<PLYINFO> info;
	VECTOR3 position; // push matrix ->������ ��ġ��ŭ translate �� ������ �׸��� ->popmatrix
	VECTOR3 angle;
	int type;
	VECTOR3 size;

public:
	Object();
	Object(VECTOR3 vec);
	virtual ~Object();
	void draw();
	void loadPLY(std::string path);

	void setPos(VECTOR3 vec);
	void setRotation(VECTOR3 vec);

	std::vector<PLYINFO> getVector();
	void setVector(std::vector<PLYINFO> vect);
	VECTOR3 getPos();

	VECTOR3 getSize();
	void setSize(VECTOR3 _size);
	
};

