#pragma once

#include <vector>
#include <string>
#include <gl/freeglut.h>
#include <iostream>

#include "Struct.h"

class Tile
{
private:
	int type;
	std::vector<PLYINFO> info;
	VECTOR3 position; // push matrix ->������ ��ġ��ŭ translate �� ������ �׸��� ->popmatrix
	VECTOR3 angle;

public:
	Tile();
	Tile(VECTOR3 vec);
	virtual ~Tile();
	void draw();
	void loadPLY(std::string path);

	void setPos(VECTOR3 vec);
	void setRotation(VECTOR3 vec);

	std::vector<PLYINFO> getVector();
	void setVector(std::vector<PLYINFO> vect);
};

