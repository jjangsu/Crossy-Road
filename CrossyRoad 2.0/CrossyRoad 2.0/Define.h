#pragma once

#define WIDTH 800
#define HEIGHT 1000

#define ROW 40
#define COL 1000

#define PUPLE_NUM 10

//tile type
#define NONE 0
#define GRASS 1
#define ROAD 2
#define TREE 3
#define RAIL 4


// car type
#define CAR 1
#define MINICAR 2
#define VEHICLE 3
#define TAXI 4
#define REDTRUCK 5
#define BLUETRUCK 6

//Object move 
#define MOVEDISTANCE 40
#define KEYLEFT 100
#define KEYUP 101
#define KEYRIGHT 102
#define KEYDOWN 103

//Obstacle type
#define BIGTREE 1
#define SMALLTREE 2
#define BIGSTONE 3
#define SMALLSTONE 4

//왼쪽오른쪽
#define LEFTEDGE -800
#define RIGHTEDGE 800

//충돌체크를위해 절반만
#define CARWIDTH 26
#define VECHILEWIDTH 34
#define TAXIWIDTH 26
#define MINICARWIDTH 20
