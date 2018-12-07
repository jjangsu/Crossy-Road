#pragma once

#include <vector>
#include <string>
#include <gl/freeglut.h>
#include <iostream>
#include <time.h>

#include "Struct.h"

class Tile
{
private:
	int type;
	int direction;
	std::vector<PLYINFO> info;
	VECTOR3 position; // push matrix ->포지션 위치만큼 translate 한 다음에 그리기 ->popmatrix
	VECTOR3 angle;
	time_t madeCarTime = 0;

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

