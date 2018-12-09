#pragma once

#include <list>

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Obstacle.h"
#include "Tile.h"
#include "Define.h"
#include "Character.h"
#include "Car.h"


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

Character character{ { 0, 0, 0 } };

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

Car train;
std::vector<PLYINFO> usingTrainVector;

Tile grass{ {0, 0, 0} };
Tile road{ {0,0,0} };
Tile rail{ {0, 0, 0} };


std::vector<PLYINFO> usingGrassVector;
std::vector<PLYINFO> usingRoadVector;
std::vector<PLYINFO> usingRailVector;


Obstacle bigTree;

Obstacle smallTree;

Obstacle bigStone;

Obstacle smallStone;

std::vector<PLYINFO> usingBigTreeVector;
std::vector<PLYINFO> usingSmallTreeVector;
std::vector<PLYINFO> usingBigStoneVector;
std::vector<PLYINFO> usingSmallStoneVector;




Tile* fixedTileArray;
//std::vector< std::vector<Obstacle> > fixedObstacle (COL,std::vector<Obstacle>(ROW));
//std::list<Obstacle> fixedObstacle(ROW*COL);
Obstacle** fixedObstacle;

std::random_device rd;
std::uniform_real_distribution<float> carSpeedRange(100, 250);
//std::uniform_int_distribution<int> carSpeedRange(1, 5);
std::uniform_int_distribution<int> carType(1, 6);
std::uniform_int_distribution<int> TileType(1, 4);
std::uniform_int_distribution<int> MakeCarPeriod(1300, 8000);
std::uniform_int_distribution<int> MakeObstacleRange(-30, 4);
std::uniform_int_distribution<int> trainSpeedRange(600, 1000);
std::uniform_int_distribution<int> MakeTrainPeriod(3000, 8000);

GLfloat AmbientLight[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat DiffuseLight[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat SpecularLight[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat lightPos[] = { 200, 100.0, cameraPos.z + 0, 1.0 };
int Specular = 60;
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };