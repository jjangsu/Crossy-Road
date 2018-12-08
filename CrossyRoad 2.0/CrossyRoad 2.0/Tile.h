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
	clock_t CarMake = clock();
	double period;
	float carSpeed;

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
	clock_t getCMake();
	void setCMake(clock_t time);
	double getPeriod();
	void setPeriod(double cycle);

	int getDirection();
	void setDirection(int dir);
	void setCarSpeed(float _speed);
	float getCarSpeed();

	void setType(int t);
	int getType();
};

