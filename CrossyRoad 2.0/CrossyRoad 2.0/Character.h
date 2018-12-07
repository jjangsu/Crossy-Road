#pragma once
#include <vector>
#include <gl/freeglut.h>
#include "Struct.h"

class Character
{
protected:
	std::vector<PLYINFO> info;
	VECTOR3 position; // push matrix ->포지션 위치만큼 translate 한 다음에 그리기 ->popmatrix
	VECTOR3 angle;
	int type;

public:
	Character();
	Character(VECTOR3 vec);
	virtual ~Character();
	void draw();
	void loadPLY(std::string path);

	void setPos(VECTOR3 vec);
	void setRotation(VECTOR3 vec);

	std::vector<PLYINFO> getVector();
	void setVector(std::vector<PLYINFO> vect);
	VECTOR3 getPos();

	
};

