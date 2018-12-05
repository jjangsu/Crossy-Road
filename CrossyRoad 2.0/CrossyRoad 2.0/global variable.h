#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Struct.h"
#include "Object.h"
#include "Define.h"

Object chicken{ {50,0,0} };
Object puplecar{ {-50,0,0} };
Object grass{ {50,0,-1} };

std::vector<Object> objVectorContainer;
Object fixedObjectArray[COL][ROW];

std::vector<PLYINFO> usingGrassVector;