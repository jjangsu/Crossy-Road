#include "InGameScene.h"


InGameScene::InGameScene()
{
}


InGameScene::~InGameScene()
{
}

void InGameScene::initialize()
{

}

void InGameScene::render()
{
	
}

void InGameScene::update()
{
	
}

void InGameScene::Terminate()
{

}

bool InGameScene::collide(VECTOR3 a, VECTOR3 sizeA, VECTOR3 b, VECTOR3 sizeB)
{
	if (a.x - sizeA.x / 2 > b.x + sizeB.x / 2)
		return false;
	if (a.x + sizeA.x / 2 < b.x - sizeB.x / 2)
		return false;
	if (a.z - sizeA.z / 2 > b.z + sizeB.z / 2)
		return false;
	if (a.z + sizeA.z / 2 < b.z - sizeB.z / 2)
		return false;

	return true;
}
