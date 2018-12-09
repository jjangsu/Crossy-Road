#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <random>
#include <chrono>
#include <vector>
#include "Tile.h"
#include "Obstacle.h"
#include "Time.h"

#include "global variable.h"
#include "Define.h"



Time frame;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void spckeycallback(int key, int x, int y);

bool collide(VECTOR3 a, VECTOR3 sizeA, VECTOR3 b, VECTOR3 sizeB)
{
	if (a.x - sizeA.x / 2 > b.x + sizeB.x / 2)
		return false;
	if (a.x + sizeA.x / 2 < b.x - sizeB.x / 2)
		return false;
	if (a.z - sizeA.z / 2 > b.z + sizeB.z / 2)
		return false;
	if (a.z + sizeA.z / 2 < b.z - sizeB.z / 2)
		return false;

	return true;
}

void gamingRander()
{
	glPushMatrix();
	{
		glShadeModel(GL_SMOOTH);
		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		glRotatef(-90, 0.0, 0.0, 1.0);
		glScalef(30.0, 20.0, 20.0);
		glutSolidCube(1.0);
		glPopMatrix();
		// 조명

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);

		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);


		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos); //위치


		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 64);

		glEnable(GL_LIGHT0);

		//glShadeModel(GL_FLAT);
		//glEnable(GL_NORMALIZE);

	}
	glPopMatrix();

	//glPushMatrix();
	//glColor3f(0, 0, 0);
	//glTranslatef(character.getPos().x, character.getPos().y+30, character.getPos().z);
	////glRotatef(-90, 0.0, 0.0, 1.0);
	////glScalef(30.0, 20.0, 20.0);
	//glutSolidSphere(20.0, 16, 16);
	//glPopMatrix();

	glPushMatrix();
	{
		character.draw();

		for (auto& v : CarArray)
			v.draw();

		for (int i = character.getPos().z / 40 - 5; i < character.getPos().z / 40 + 30; ++i) {
			if (fixedTileArray[i].getType() == RAIL)
				fixedTileArray[i].drawRail();
			else
				fixedTileArray[i].draw();
		}
	}
	glPopMatrix();
}

int main(int argc, char *argv[])
{
	srand((unsigned int)time(nullptr));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(400, 0); // 윈도우의 위치지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	glutTimerFunc(1000 / 60, TimerFunction, 1); // 타이머 함수 설정 	

	glutCreateWindow("Corry Road"); // 윈도우 생성 (윈도우 이름)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // 출력 함수의 지정


	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);
	glutSpecialFunc(spckeycallback);

	cameraPos = { -20.f, 35.f, -60.f };

	fixedTileArray = new Tile[COL];

	// 캐릭터
	character.loadPLY("resource/chicken.ply");
	character.setPos({ 0,0,0, });
	character.setSize({ 20, 40, 30 });

	// 차
	pupleCar.loadPLY("resource/puple car.ply");
	usingCarVector = pupleCar.getVector();

	miniCar.loadPLY("resource/blue mini car.ply");
	usingMiniCarVector = miniCar.getVector();

	orangeCar.loadPLY("resource/orange car.ply");
	usingvehicleVector = orangeCar.getVector();

	taxi.loadPLY("resource/taxi.ply");
	usingTaxiVector = taxi.getVector();

	redTruck.loadPLY("resource/truck red.ply");
	usingRedTruckVector = redTruck.getVector();

	blueTruck.loadPLY("resource/truck blue.ply");
	usingBlueTruckVector = blueTruck.getVector();

	// 타일
	grass.loadPLY("resource/grass.ply");
	usingGrassVector = grass.getVector();

	road.loadPLY("resource/temproad.ply");
	usingRoadVector = road.getVector();

	rail.loadPLY("resource/railway.ply");
	usingRailVector = rail.getVector();

	bigStone.loadPLY("resource/large stone.ply");
	usingBigStoneVector = bigStone.getVector();

	smallStone.loadPLY("resource/stone.ply");
	usingSmallStoneVector = smallStone.getVector();

	bigTree.loadPLY("resource/long tree.ply");
	usingBigTreeVector = bigTree.getVector();

	smallTree.loadPLY("resource/small tree.ply");
	usingSmallTreeVector = smallTree.getVector();


	
	//for (int i = 0; i < COL; ++i)
	//{
	//	for (int j = 0; j < ROW; ++j)
	//	{
	//		std::cout << i << " " << j << " 되냐?" << std::endl;
	//		int tempType = MakeObstacleRange(rd);
	//		if (tempType <= 0)
	//		{
	//			fixedObstacle[i][j].setType(NONE);
	//			fixedObstacle[i][j].setPos({ (j - 40) * 40.f,0.f,i * 40.f });
	//		}
	//		else if (tempType == BIGTREE)
	//		{
	//			fixedObstacle[i][j].setType(tempType);
	//			fixedObstacle[i][j].setPos({ (j - 40) * 40.f,0.f,i * 40.f });
	//			fixedObstacle[i][j].setVector(usingBigTreeVector);
	//		}

	//		else if (tempType == SMALLTREE)
	//		{
	//			fixedObstacle[i][j].setType(tempType);
	//			fixedObstacle[i][j].setPos({ (j - 40) * 40.f,0.f,i * 40.f });
	//			fixedObstacle[i][j].setVector(usingSmallTreeVector);
	//		}

	//		else if (tempType == BIGSTONE)
	//		{
	//			fixedObstacle[i][j].setType(tempType);
	//			fixedObstacle[i][j].setPos({ (j - 40) * 40.f,0.f,i * 40.f });
	//			fixedObstacle[i][j].setVector(usingBigStoneVector);
	//		}

	//		else //if (tempType == SMALLSTONE)
	//		{
	//			fixedObstacle[i][j].setType(tempType);
	//			fixedObstacle[i][j].setPos({ (j - 40) * 40.f,0.f,i * 40.f });
	//			fixedObstacle[i][j].setVector(usingSmallStoneVector);
	//		}

	//	
	//	}
	//}

	int listI = 0, listJ = 0;

	for (auto iter = fixedObstacle.begin(); iter != fixedObstacle.end();)
	{
		for (int i = 0; i < COL; ++i)
		{
			for (int j = 0; j < ROW; ++j)
			{
				int tempType = MakeObstacleRange(rd);
				if (tempType <= 0)
				{
					iter->setType(NONE);
					iter->setPos({ (j - 40) * 40.f,0.f,i * 40.f });
				}
				else if (tempType == BIGTREE)
				{
					iter->setType(tempType);
					iter->setPos({ (j - 40) * 40.f,0.f,i * 40.f });
					//iter->setVector(usingBigTreeVector);
				}

				else if (tempType == SMALLTREE)
				{
					iter->setType(tempType);
					iter->setPos({ (j - 40) * 40.f,0.f,i * 40.f });
					//iter->setVector(usingSmallTreeVector);
				}

				else if (tempType == BIGSTONE)
				{
					iter->setType(tempType);
					iter->setPos({ (j - 40) * 40.f,0.f,i * 40.f });
					//iter->setVector(usingBigStoneVector);
				}

				else //if (tempType == SMALLSTONE)
				{
					iter->setType(tempType);
					iter->setPos({ (j - 40) * 40.f,0.f,i * 40.f });
					//iter->setVector(usingSmallStoneVector);
				}
				++iter;
			}
		}
	}

	std::cout << "오냐?" << std::endl;
	
	for (int i = 0; i < COL; ++i) {	// z
		
		fixedTileArray[i].setPos({ 0.f, -1.f, i * 40.f });
		int tempType = TileType(rd);
		if (tempType == GRASS)
		{
			fixedTileArray[i].setVector(usingGrassVector);
			fixedTileArray[i].setType(GRASS);
		}
		else if (tempType == ROAD || tempType == TREE)
		{
			fixedTileArray[i].setVector(usingRoadVector);
			fixedTileArray[i].setType(ROAD);
		}
		else if (tempType == RAIL) {
			fixedTileArray[i].setVector(usingRailVector);
			fixedTileArray[i].setType(RAIL);
		}
		fixedTileArray[i].setCMake(clock());
		fixedTileArray[i].setPeriod(MakeCarPeriod(rd));
		fixedTileArray[i].setCarSpeed(carSpeedRange(rd));
		int tempdir = TileType(rd);
		if (tempdir == 1)
		{
			fixedTileArray[i].setDirection(1);
		}
		else
		{
			fixedTileArray[i].setDirection(-1);
		}
	}
	
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(105 / 255.f, 204 / 255.f, 236 / 255.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	gluLookAt(
		cameraPos.x, cameraPos.y, cameraPos.z,
		cameraAt.x, cameraAt.y, cameraAt.z,
		0.0, 1.0, 0.0);

	if (currentScene == gaming) 
	{
		gamingRander();
	}

	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}

void TimerFunction(int value)
{
	lightPos[0] = character.getPos().x + 40;
	lightPos[1] = character.getPos().y + 80;
	lightPos[2] = character.getPos().z + 30;


	// 카메라 자동이동 
	cameraPos.z += 1.0;
	cameraAt.z = cameraPos.z + 20.f;

	// 카메라 캐릭터와의 거리와 비교해서 따라가기 
	if (cameraMoveToChar) 
	{
		VECTOR3 temp = character.getPos();
		cameraPos.z += cameraMove * fabs(cameraPos.z - temp.z);
		cameraAt.z = cameraPos.z + 20.f;
		if (abs(cameraPos.z - temp.z) < 60) {
			cameraPos.z = temp.z - 60;
			cameraAt.z = cameraPos.z + 20;
			cameraMoveToChar = false;
		}
	}
	
	if (MoveToCharX)
	{
		VECTOR3 temp = character.getPos();
		cameraPos.x += cameraMove * fabs(temp.x - cameraPos.x);
		cameraAt.x = cameraPos.x + 20;
		if (fabs(temp.x - cameraPos.x) < 40)
		{
			cameraPos.x = temp.x - 40;
			cameraAt.x = cameraPos.x + 20;
			MoveToCharX = false;
		}
	}

	//충돌체크?
	for (auto& iter : CarArray)
	{
		if (abs(iter.getPos().z - character.getPos().z) <= 80)
		{
			VECTOR3 car = iter.getPos();
			VECTOR3 carSize = iter.getSize();
			VECTOR3 charac = character.getPos();
			VECTOR3 characSize = character.getSize();

			if (collide(car, carSize, charac, characSize))
				exit(1);
		}
	}

	//update Car
	for (auto& v : CarArray)
		v.move();

	//Release Car
	for (auto iter = CarArray.begin(); iter != CarArray.end();)
	{
		if ((character.getPos().z - iter->getPos().z) / 40 > 20 || (iter->getPos().z - character.getPos().z) / 40 < -5)
		{
			iter = CarArray.erase(iter);
		}
		else if (abs(iter->getPos().x) > RIGHTEDGE)
		{
			iter = CarArray.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	int charz = character.getPos().z / 40;
	clock_t currenttime = clock();

	//Making Car
	for (int i = charz - 20; i < charz + 20; ++i)
	{
		if (i >= 0)
		{
			if (currenttime - fixedTileArray[i].getCMake() > fixedTileArray[i].getPeriod() && fixedTileArray[i].getType() == ROAD)
			{
				Car tempcar{ { 700.f * -fixedTileArray[i].getDirection(), 0.f, i * 40.f } };
				tempcar.setDir();

				int tempType = carType(rd);
				if (tempType == CAR) {
					tempcar.setVector(usingCarVector);
					tempcar.setSize({ 40, 40, 40 });
				}
				else if (tempType == MINICAR) {
					tempcar.setVector(usingMiniCarVector);
					tempcar.setSize({ 30, 40, 40 });
				}
				else if (tempType == VEHICLE) {
					tempcar.setVector(usingvehicleVector);
					tempcar.setSize({ 40, 40, 40 });
				}
				else if (tempType == TAXI) {
					tempcar.setVector(usingTaxiVector);
					tempcar.setSize({ 30, 40, 40 });
				}
				else if (tempType == REDTRUCK) {
					tempcar.setVector(usingRedTruckVector);
					tempcar.setSize({ 100, 40, 40 });
				}
				else if (tempType == BLUETRUCK) {
					tempcar.setVector(usingBlueTruckVector);
					tempcar.setSize({ 100, 40, 40 });
				}

				tempcar.setSpeed(fixedTileArray[i].getCarSpeed());
				CarArray.push_back(tempcar);
				fixedTileArray[i].setCMake(clock());

			}
		}
	}


	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		cameraAt.y -= 10.0;
		cameraPos.y -= 10.0;
		break;
	case 's':
		cameraAt.y += 10.0;
		cameraPos.y += 10.0;
		break;
	case 'a':
		cameraAt.x += 10.0;
		cameraPos.x += 10.0;
		break;
	case 'd':
		cameraAt.x -= 10.0;
		cameraPos.x -= 10.0;
		break;
	case 'e':
		cameraAt.z -= 10.0;
		cameraPos.z -= 10.0;
		break;
	case 'q':
		cameraAt.z += 10.0;
		cameraPos.z += 10.0;
		break;
	case 'x':
		cameraAt.y -= 10.0;
		break;
	case 'X':
		cameraAt.y += 10.0;
		break;
		// 카메라 y회전
	case 'y':
		cameraAt.x += 10.0;
		break;
	case 'Y':
		cameraAt.x -= 10.0;
		break;
		// 카메라 z회전
	case 'z':
		cameraAt.z -= 10.0;
		break;
	case 'Z':
		cameraAt.z += 10.0;

		break;
	case 27:
		exit(1);
	default:
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (float)w / h, 0.1, 1000);
	glTranslated(0, 0, -120);
}

void spckeycallback(int key, int x, int y)
{
	VECTOR3 temp;
	switch (key)
	{
	case KEYUP:
		temp = character.getPos();
		character.setPos({ temp.x,temp.y,temp.z + MOVEDISTANCE });
		character.setRotation({ 0, 0, 0 });
		if (abs(temp.z + MOVEDISTANCE - cameraPos.z) > 60.f) {
			cameraMoveToChar = true;
		}
		break;

	case KEYDOWN:
		temp = character.getPos();
		character.setPos({ temp.x,temp.y,temp.z - MOVEDISTANCE });
		character.setRotation({ 0, 180, 0 });
		break;

	case KEYLEFT:
		temp = character.getPos();
		character.setPos({ temp.x + MOVEDISTANCE,temp.y,temp.z });
		character.setRotation({ 0, 90, 0 });
		MoveToCharX = true;
		//cameraPos.x = cameraPos.x - 40;
		//cameraAt.x = cameraPos.x + 20;
		break;

	case KEYRIGHT:
		temp = character.getPos();
		character.setPos({ temp.x - MOVEDISTANCE,temp.y,temp.z });
		character.setRotation({ 0, -90, 0 });
		MoveToCharXminus = true;
		cameraPos.x = cameraPos.x - 40;
		cameraAt.x = cameraPos.x + 20;
		break;
	}
}
