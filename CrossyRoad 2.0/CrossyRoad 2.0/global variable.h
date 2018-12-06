#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Define.h"
#include "Character.h"

#define width 800
#define height 600

VECTOR3 cameraPos{ 0.f, 20.f, 100.f };
VECTOR3 cameraAt{ 0, 0, 0 };

Character chicken{ { 50, 0, 0 } };
Character pupleCar{ { -50,0,0 } };

Tile grass{ {50, 0, -1} };

Tile fixedTileArray[COL][ROW];

std::vector<PLYINFO> usingGrassVector;