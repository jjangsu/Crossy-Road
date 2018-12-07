#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Define.h"
#include "Character.h"
#include "Car.h"


VECTOR3 cameraPos{ 0.f, 20.f, -60.f };
VECTOR3 cameraAt{ 0, 10, cameraPos.z + 20 };

Character character{ { 0, 0, 0 } };

Car pupleCar{ { -500,0,0 }, 5 };
Car miniCar;
std::vector<Car> CarArray;
std::vector<PLYINFO> usingCarVector;


Tile grass{ {0, 0, 0} };
Tile road{ {0,0,0} };

Tile fixedTileArray[COL];

std::random_device rd;
std::uniform_int_distribution<int> carSpeedRange(5, 10);
std::uniform_int_distribution<int> TrueOrFalse(0, 1);
std::uniform_int_distribution<int> MakeCarPeriod(1000, 10000);


std::vector<PLYINFO> usingGrassVector;
std::vector<PLYINFO> usingRoadVector;