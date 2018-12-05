#pragma once

#include <vector>
#include <string>
#include <gl/freeglut.h>
#include <iostream>

#include "Struct.h"

class Object
{
protected:
	std::vector<PLYINFO> info;
	VECTOR3 position; // push matrix ->������ ��ġ��ŭ translate �� ������ �׸��� ->popmatrix

public:
	Object();
	Object(VECTOR3 vec);
	virtual ~Object();
	void draw();
	void loadPLY(std::string path);
};

