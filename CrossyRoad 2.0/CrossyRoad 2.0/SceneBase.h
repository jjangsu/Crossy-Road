#pragma once
#include <GL/freeglut.h>
#include <random>
#include <iostream>
#include <string>
#include <vector>


class SceneBase
{
public:
	enum SceneType{
		intro, 
		inGame,
	};
public:
	SceneBase();
	~SceneBase();

	void initialize();
	void render();
	void update();
	void Terminate();

};

