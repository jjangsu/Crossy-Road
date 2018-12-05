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
	VECTOR3 position; // push matrix ->포지션 위치만큼 translate 한 다음에 그리기 ->popmatrix

public:
	Object();
	Object(VECTOR3 vec);
	virtual ~Object();
	void draw();
	void loadPLY(std::string path);
};

