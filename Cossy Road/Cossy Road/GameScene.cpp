#include <random>
#include <chrono>

#include "GameScene.h"
#include "controls.hpp"

float Object3d::radian = 0;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::initialize()
{
	//for (int i = 0; i < 400; ++i) {
	for (int j = 0; j < 15; ++j) {
		for (int k = 0; k < 50; ++k) {
			grass[j][k].position = { -3.f + (j)* 0.4f, -0.03f, -14.f + (k + 1) * 0.4f };
			grass[j][k].initialize();
		}
	}
	//}

	//for (auto& v : chicken)
	chicken.initialize();
}

void GameScene::update()
{
	//Object3d::radian += 0.01f;
	Object3d::radian = 120.f * 3.14 / 180.f;

	computeMatricesFromInputs();

	for (int j = 0; j < 15; ++j) {
		for (int k = 0; k < 50; ++k) {
			grass[j][k].update();
		}
	}
	//for (auto& v : chicken)
	chicken.update();
}

void GameScene::render()
{
	for (int j = 0; j < 15; ++j) {
		for (int k = 0; k < 50; ++k) {
			grass[j][k].render();
		}
	}
	//for (auto& v : chicken)
	chicken.render();
}

void GameScene::release()
{
	for (int j = 0; j < 15; ++j) {
		for (int k = 0; k < 50; ++k) {
			grass[j][k].release();
		}
	}
	//for (auto& v : chicken)
	chicken.release();
}