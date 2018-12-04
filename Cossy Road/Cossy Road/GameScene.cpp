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
	for (int j = 0; j < 25; ++j) {
		for (int k = 0; k < 25; ++k) {
			grass[j][k].position = { -5.0f + (j)* 0.4f, -0.03f, -5.0f + (k + 1) * 0.4f };
			grass[j][k].initialize();
		}
	}
	//}

	//for (auto& v : grass)
	// v.initialize();
	for (auto& v : babychicken)
		v.initialize();
	for (auto& v : chicken)
		v.initialize();
}

void GameScene::update()
{
	//Object3d::radian += 0.01f;
	Object3d::radian = 120.f * 3.14 / 180.f;

	computeMatricesFromInputs();

	for (int j = 0; j < 25; ++j) {
		for (int k = 0; k < 25; ++k) {
			grass[j][k].update();
		}
	}
	//for (auto& v : grass)
	//	v.update();
	for (auto& v : babychicken)
		v.update();
	for (auto& v : chicken)
		v.update();
}

void GameScene::render()
{
	for (int j = 0; j < 25; ++j) {
		for (int k = 0; k < 25; ++k) {
			grass[j][k].render();
		}
	}
	//for (auto& v : grass)
	//	v.render();
	for (auto& v : babychicken)
		v.render();
	for (auto& v : chicken)
		v.render();
}

void GameScene::release()
{
	for (int j = 0; j < 25; ++j) {
		for (int k = 0; k < 25; ++k) {
			grass[j][k].release();
		}
	}
	//for (auto& v : grass)
	//	v.release();
	for (auto& v : babychicken)
		v.release();
	for (auto& v : chicken)
		v.release();
}