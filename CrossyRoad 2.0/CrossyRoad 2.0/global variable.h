#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Define.h"
#include "Object.h"
#include "Chicken.h"
#include "Car.h"

enum scene {intro, chooseChar, gaming, gameover};
int currentScene = gaming;

VECTOR3 cameraPos{ 0.f, 20.f, -60.f };
VECTOR3 cameraAt{ 0, 10, cameraPos.z + 20 };

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


Tile grass{ {0, 0, 0} };
Tile road{ {0,0,0} };

std::vector<PLYINFO> usingGrassVector;
std::vector<PLYINFO> usingRoadVector;

Tile* fixedTileArray;

std::random_device rd;
std::uniform_real_distribution<float> carSpeedRange(0.3, 1.0);
//std::uniform_int_distribution<int> carSpeedRange(1, 5);
std::uniform_int_distribution<int> carType(1, 4);
std::uniform_int_distribution<int> TileType(0, 1);
std::uniform_int_distribution<int> MakeCarPeriod(500, 5000);


