#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Define.h"

#define width 800
#define height 600

VECTOR3 cameraPos{ 0.f, 20.f, 100.f };
VECTOR3 cameraAt{ 0, 0, 0 };

Object chicken{ { 50, 0, 0 } };
Object pupleCar{ { -50,0,0 } };

Object grass{ {50, 0, -1} };

Object fixedObjectArray[COL][ROW];

std::vector<PLYINFO> usingGrassVector;