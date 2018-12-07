#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Define.h"
#include "Object.h"
#include "Chicken.h"
#include "Car.h"


VECTOR3 cameraPos{ 0.f, 20.f, -60.f };
VECTOR3 cameraAt{ 0, 10, cameraPos.z + 20 };

Chicken chicken{ { 0, 0, 0 } };

Car pupleCar{ { -500,0,0 }, 5 };
std::vector<Car> CarArray;
std::vector<PLYINFO> usingCarVector;

Car miniCar;
std::vector<PLYINFO> usingMiniCarVector;

Car orangeCar;
std::vector<PLYINFO> usingOrangeCarVector;

Car taxi;
std::vector<PLYINFO> usingTaxiVector;


Tile grass{ {0, 0, 0} };
Tile road{ {0,0,0} };

std::vector<PLYINFO> usingGrassVector;
std::vector<PLYINFO> usingRoadVector;

Tile fixedTileArray[COL];

std::random_device rd;
std::uniform_int_distribution<int> carSpeedRange(5, 10);
std::uniform_int_distribution<int> carType(1, 4);
std::uniform_int_distribution<int> TileType(0, 1);
std::uniform_int_distribution<int> MakeCarPeriod(1000, 10000);


