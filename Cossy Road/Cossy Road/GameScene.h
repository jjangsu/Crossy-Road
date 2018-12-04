#pragma once
#include <random>
#include <chrono>
#include "Scene.h"
#include "Object3d.h"

class Tree
{
	Object3d obj;
public:

	void initialize()
	{
		std::uniform_int_distribution<int> uid_7(0, 6);
		std::uniform_int_distribution<int> uid_360(1, 360);
		std::uniform_int_distribution<int> uid_200(-100, 100);
		std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

		obj.setBMP("resources/T_PolygonCity_Texture_01_A.bmp");
		switch (uid_7(dre)) {
		case 1: obj.setOBJ("resources/SM_Env_Tree_01_Internal.obj"); break;
		case 2: obj.setOBJ("resources/SM_Env_Tree_02_Internal.obj"); break;
		default: obj.setOBJ("resources/SM_Env_Tree_03_Internal.obj"); break;
		}
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		obj.setRotation(0, float(uid_360(dre)), 0);
		obj.setScale(1 + float(uid_200(dre) / 200.f));
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class Grass
{
	Object3d obj;
public:
	glm::vec3 position;
public:

	void initialize()
	{
		static std::uniform_int_distribution<int> uid_10(-5, 5);
		//static std::uniform_int_distribution<int> uid_200(0, 10);
		static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

		obj.setBMP("resource/ground/grass 01.bmp");
		obj.setOBJ("resource/ground/grass 01.obj");
		obj.initialize();
		obj.setPosition(position.x, position.y, position.z);
		//obj.setPosition(uid_10(dre), -0.05f, uid_10(dre) * 1.f);
		obj.setRotation(0, 0, 0);
		obj.setScale(5.f);
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class Chicken
{
	Object3d obj;
public:

	void initialize()
	{
		static std::uniform_int_distribution<int> uid_360(1, 360);
		static std::uniform_int_distribution<int> uid_200(-100, 100);
		static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());
		
		obj.setBMP("resource/character object/chicken.bmp");
		obj.setOBJ("resource/character object/chicken.obj");
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		//obj.setRotation(0, float(uid_360(dre)), 0);
		obj.setRotation(0, 0, 0);
		obj.setScale(2 + uid_200(dre) / 200.f);
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class BabyChicken
{
	Object3d obj;
public:

	void initialize()
	{
		static std::uniform_int_distribution<int> uid_360(1, 360);
		static std::uniform_int_distribution<int> uid_200(-100, 100);
		static std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

		obj.setBMP("resource/character object/chickenbaby.bmp");
		obj.setOBJ("resource/character object/chickenbaby.obj");
		obj.initialize();
		obj.setPosition(uid_200(dre) / 20.f, 0, uid_200(dre) / 20.f);
		obj.setRotation(0, 0, 0);
		//obj.setRotation(0, float(uid_360(dre)), 0);
		obj.setScale(1 + uid_200(dre) / 200.f);
	}
	void update()
	{
		obj.update();
	}
	void render()
	{
		obj.render();
	}
	void release()
	{
		obj.release();
	}
};

class GameScene : public Scene
{
	Grass grass[25][25];
	Chicken chicken[50];
	BabyChicken babychicken[150];
public:
	GameScene();
	~GameScene();

	void initialize();
	void update();
	void render();
	void release();
};