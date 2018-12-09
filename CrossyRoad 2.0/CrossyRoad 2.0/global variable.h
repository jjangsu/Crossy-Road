#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Define.h"
#include "Object.h"
#include "Chicken.h"
#include "Car.h"
#include "Obstacle.h"
#include <list>

enum CURRENTSCENE {intro, gaming, gameover};
int currentScene = gaming;

Time frame;

VECTOR3 cameraPos{ -20.f, 40.f, -60.f };
VECTOR3 cameraAt{ cameraPos.x + 5, 10, cameraPos.z + 20 };
bool cameraMoveToChar = false;
float cameraMove = 0.05;
bool MoveToCharX = false;
//float moveX = 0.05;
bool MoveToCharXminus = false;

Chicken character{ { 0, 0, 0 } };

Car pupleCar;
std::vector<Car> CarArray;
std::vector<PLYINFO> usingCarVector;

Car miniCar;
std::vector<PLYINFO> usingMiniCarVector;

Car orangeCar;
std::vector<PLYINFO> usingvehicleVector;

Car taxi;
std::vector<PLYINFO> usingTaxiVector;

Car redTruck;
std::vector<PLYINFO> usingRedTruckVector;

Car blueTruck;
std::vector<PLYINFO> usingBlueTruckVector;

Tile grass{ {0, 0, 0} };
Tile road{ {0,0,0} };
Tile rail{ {0, 0, 0} };


std::vector<PLYINFO> usingGrassVector;
std::vector<PLYINFO> usingRoadVector;
std::vector<PLYINFO> usingRailVector;

Obstacle bigTree;
std::vector<PLYINFO> usingBigTreeVector;

Obstacle smallTree;
std::vector<PLYINFO> usingSmallTreeVector;

Obstacle bigStone;
std::vector<PLYINFO> usingBigStoneVector;

Obstacle smallStone;
std::vector<PLYINFO> usingSmallStoneVector;


Tile* fixedTileArray;
//std::vector< std::vector<Obstacle> > fixedObstacle (COL,std::vector<Obstacle>(ROW));
std::list<Obstacle> fixedObstacle(ROW*COL);

std::random_device rd;
std::uniform_real_distribution<float> carSpeedRange(100, 250);
//std::uniform_int_distribution<int> carSpeedRange(1, 5);
std::uniform_int_distribution<int> carType(1, 6);
std::uniform_int_distribution<int> TileType(1, 4);
std::uniform_int_distribution<int> MakeCarPeriod(700, 8000);
std::uniform_int_distribution<int> MakeObstacleRange(-10, 4);

GLfloat AmbientLight[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat DiffuseLight[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat SpecularLight[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat lightPos[] = { 200, 100.0, cameraPos.z + 0, 1.0 };
int Specular = 60;
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };