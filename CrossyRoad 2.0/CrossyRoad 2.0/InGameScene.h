#pragma once
#include "SceneBase.h"
#include "Tile.h"
#include "Define.h"
#include "Car.h"
#include "Chicken.h"
#include "Obstacle.h"

class InGameScene : public SceneBase
{
public:

public:
	InGameScene();
	~InGameScene();

	void initialize();
	void render();
	void update();
	void Terminate();

	bool collide(VECTOR3 a, VECTOR3 sizeA, VECTOR3 b, VECTOR3 sizeB);

};

