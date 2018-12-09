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


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void spckeycallback(int key, int x, int y);
bool collide(VECTOR3 a, VECTOR3 sizeA, VECTOR3 b, VECTOR3 sizeB);
void gameInit();
void gamingRander();
void gamingUpdate();
void introInit();
void introRander();
void introUpdate();


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

int main(int argc, char *argv[])
{
	srand((unsigned int)time(nullptr));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(400, 0); // 윈도우의 위치지정
	glutInitWindowSize(WIDTH, HEIGHT); // 윈도우의 크기 지정
	glutTimerFunc(1, TimerFunction, 1); // 타이머 함수 설정 	

	glutCreateWindow("Corry Road"); // 윈도우 생성 (윈도우 이름)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // 출력 함수의 지정


	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);
	glutSpecialFunc(spckeycallback);

	//introInit();
	gameInit();

	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClearColor(105 / 255.f, 204 / 255.f, 236 / 255.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	switch (currentScene)
	{
	case gaming:
		gamingRander();
		break;
	case intro:
		introRander();
		break;
	default:
		break;
	}


	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}

void TimerFunction(int value)
{
	gamingUpdate();

	if (finish)
	{
		character.setScale({ 1.0, 0.1, 1.0 });
	}

	glutPostRedisplay();
	glutTimerFunc(1, TimerFunction, 1);
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


void Keyboard(unsigned char key, int x, int y)
{
	if (!finish)
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
			cameraAt.x -= 10.0;
			if (firstPerson)
			{
				firstPersonAt.x -= 10.0;
			}
			break;
		case 'X':
			cameraAt.x += 10.0;
			if (firstPerson)
			{
				firstPersonAt.x += 10.0;
			}
			break;
			// 카메라 y회전
		case 'y':
			cameraAt.y += 10.0;
			break;
		case 'Y':
			cameraAt.y -= 10.0;
			break;
			// 카메라 z회전
		case 'z':
			cameraAt.z -= 10.0;
			break;
		case 'Z':
			cameraAt.z += 10.0;
			break;
		case '1':
			character.setVector(chicken.getVector());
			break;
		case'2':
			character.setVector(granPa.getVector());
			break;
		case '3':
			character.setVector(knight.getVector());
			break;
		case '4':
			DiffuseLight[0] = 1.0;
			DiffuseLight[1] = 1.0;
			DiffuseLight[2] = 1.0;
			break;
		case '5':
			DiffuseLight[0] = 1.0;
			DiffuseLight[1] = 0.0;
			DiffuseLight[2] = 0.0;
			break;
		case '6':
			DiffuseLight[0] = 0.0;
			DiffuseLight[1] = 0.0;
			DiffuseLight[2] = 1.0;
			break;
		case '7':
			firstPerson = !firstPerson;
			if (!firstPerson)
			{
				cameraPos.x = character.getPos().x - 20;
				cameraPos.y = character.getPos().y + 40;
				cameraPos.z = character.getPos().z - 60;
			}
			else
			{
				cameraPos = character.getPos();
				cameraPos.y += 10;
				cameraPos.z += 150;
				cameraAt.x = cameraPos.x;
				cameraAt.z = cameraPos.z + 20;
			}
			break;
		default:
			break;
		}

	switch (key)
	{
	case ' ':
		finish = false;
		firstPerson = false;

		

		for (int i = 0; i < COL; ++i) {	// z

			fixedTileArray[i].setPos({ 0.f, -1.f, i * 40.f });
			int tempType = TileType(rd);
			if (tempType == GRASS)
			{
				fixedTileArray[i].setVector(usingGrassVector);
				fixedTileArray[i].setType(GRASS);
				fixedTileArray[i].setCMake(clock());
				fixedTileArray[i].setPeriod(MakeCarPeriod(rd));
				fixedTileArray[i].setCarSpeed(carSpeedRange(rd));
			}
			else if (tempType == ROAD || tempType == TREE)
			{
				fixedTileArray[i].setVector(usingRoadVector);
				fixedTileArray[i].setType(ROAD);
				fixedTileArray[i].setCMake(clock());
				fixedTileArray[i].setPeriod(MakeCarPeriod(rd));
				fixedTileArray[i].setCarSpeed(carSpeedRange(rd));
			}
			else if (tempType == RAIL) {
				fixedTileArray[i].setVector(usingRailVector);
				fixedTileArray[i].setType(RAIL);
				fixedTileArray[i].setCMake(clock());
				fixedTileArray[i].setPeriod(MakeTrainPeriod(rd));
				fixedTileArray[i].setCarSpeed(trainSpeedRange(rd));
			}

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

		int tempType;

		for (int i = 0; i < COL; ++i)
		{
			for (int j = 0; j < ROW; ++j) //x
			{
				tempType = MakeObstacleRange(rd);

				if (fixedTileArray[i].getType() == GRASS)
				{

					if (tempType == BIGTREE)
					{
						fixedObstacle[i][j].setType(1);
						fixedObstacle[i][j].setPos({ (j - 20) * 40.f, 0.f, i * 40.f });

					}

					else if (tempType == SMALLTREE)
					{
						fixedObstacle[i][j].setType(2);
						fixedObstacle[i][j].setPos({ (j - 20) * 40.f,0.f,i * 40.f });

					}

					else if (tempType == BIGSTONE)
					{
						fixedObstacle[i][j].setType(3);
						fixedObstacle[i][j].setPos({ (j - 20) * 40.f,0.f,i * 40.f });

					}

					else if (tempType == SMALLSTONE)
					{
						fixedObstacle[i][j].setType(4);
						fixedObstacle[i][j].setPos({ (j - 20) * 40.f,0.f,i * 40.f });
					}
					else
					{
						fixedObstacle[i][j].setType(NONE);
						fixedObstacle[i][j].setPos({ (j - 20) * 40.f, 0.f, i * 40.f });
					}
				}
				else
					fixedObstacle[i][j].setType(0);
			}
		}
		character.setPos({ 0, 0, 0 });

		cameraPos.x = - 20;
		cameraPos.y = + 40;
		cameraPos.z = - 60;
		break;
	case 27:
		exit(1);
	default:
		break;
	}

	glutPostRedisplay();
}

void spckeycallback(int key, int x, int y)
{
	VECTOR3 temp;

	int charxindex = (int)((800 + character.getPos().x) / 40);
	int charzindex = (int)(character.getPos().z / 40);


	if (!finish)
	{
		switch (key)
		{
		case KEYUP:
			if (charzindex < 1000) {
				if (fixedObstacle[charzindex + 1][charxindex].getType() == NONE)
				{
					temp = character.getPos();
					character.setPos({ temp.x,temp.y,temp.z + MOVEDISTANCE });
					character.setRotation({ 0, 0, 0 });
					if (abs(temp.z + MOVEDISTANCE - cameraPos.z) > 60.f) {
						cameraMoveToChar = true;
					}
				}
			}
			break;

		case KEYDOWN:
			if (charzindex > 0)
			{
				if (fixedObstacle[charzindex - 1][charxindex].getType() == NONE)
				{
					temp = character.getPos();
					character.setPos({ temp.x,temp.y,temp.z - MOVEDISTANCE });
					character.setRotation({ 0, 180, 0 });
				}
			}
			break;

		case KEYLEFT:
			if (charxindex < 39)
			{
				if (fixedObstacle[charzindex][charxindex + 1].getType() == NONE)
				{
					temp = character.getPos();
					character.setPos({ temp.x + MOVEDISTANCE,temp.y,temp.z });
					character.setRotation({ 0, 90, 0 });
					MoveToCharX = true;
					break;
				}
			}
			
			break;
		case KEYRIGHT:
			if (charxindex > 0)
			{
				if (fixedObstacle[charzindex][charxindex - 1].getType() == NONE)
				{
					temp = character.getPos();
					character.setPos({ temp.x - MOVEDISTANCE,temp.y,temp.z });
					character.setRotation({ 0, -90, 0 });
					MoveToCharXminus = true;
					cameraPos.x = cameraPos.x - 40;
					cameraAt.x = cameraPos.x + 5;
				}
			}
			break;
		}
	}


}

void gameInit()
{
	cameraPos = { -20.f, 35.f, -60.f };
	cameraAt = { cameraPos.x + 5, 10, cameraPos.z + 20 };

	fixedTileArray = new Tile[COL];

	// 캐릭터
	chicken.loadPLY("resource/chicken.ply");
	granPa.loadPLY("resource/granPa.ply");
	knight.loadPLY("resource/knight.ply");

	character.setVector(chicken.getVector());
	character.setPos({ 0,0,0, });
	character.setSize({ 40, 40, 30 });

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

	train.loadPLY("resource/train.ply");
	usingTrainVector = train.getVector();


	for (int i = 0; i < COL; ++i) {	// z

		fixedTileArray[i].setPos({ 0.f, -1.f, i * 40.f });
		int tempType = TileType(rd);
		if (tempType == GRASS)
		{
			fixedTileArray[i].setVector(usingGrassVector);
			fixedTileArray[i].setType(GRASS);
			fixedTileArray[i].setCMake(clock());
			fixedTileArray[i].setPeriod(MakeCarPeriod(rd));
			fixedTileArray[i].setCarSpeed(carSpeedRange(rd));
		}
		else if (tempType == ROAD || tempType == TREE)
		{
			fixedTileArray[i].setVector(usingRoadVector);
			fixedTileArray[i].setType(ROAD);
			fixedTileArray[i].setCMake(clock());
			fixedTileArray[i].setPeriod(MakeCarPeriod(rd));
			fixedTileArray[i].setCarSpeed(carSpeedRange(rd));
		}
		else if (tempType == RAIL) {
			fixedTileArray[i].setVector(usingRailVector);
			fixedTileArray[i].setType(RAIL);
			fixedTileArray[i].setCMake(clock());
			fixedTileArray[i].setPeriod(MakeTrainPeriod(rd));
			fixedTileArray[i].setCarSpeed(trainSpeedRange(rd));
		}

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

	fixedObstacle = new Obstacle*[COL];
	for (int i = 0; i < COL; ++i)
	{
		fixedObstacle[i] = new Obstacle[ROW];
	}

	int tempType;

	for (int i = 0; i < COL; ++i)
	{
		for (int j = 0; j < ROW; ++j) //x
		{
			tempType = MakeObstacleRange(rd);

			if (fixedTileArray[i].getType() == GRASS)
			{

				if (tempType == BIGTREE)
				{
					fixedObstacle[i][j].setType(1);
					fixedObstacle[i][j].setPos({ (j - 20) * 40.f, 0.f, i * 40.f });

				}

				else if (tempType == SMALLTREE)
				{
					fixedObstacle[i][j].setType(2);
					fixedObstacle[i][j].setPos({ (j - 20) * 40.f,0.f,i * 40.f });

				}

				else if (tempType == BIGSTONE)
				{
					fixedObstacle[i][j].setType(3);
					fixedObstacle[i][j].setPos({ (j - 20) * 40.f,0.f,i * 40.f });

				}

				else if (tempType == SMALLSTONE)
				{
					fixedObstacle[i][j].setType(4);
					fixedObstacle[i][j].setPos({ (j - 20) * 40.f,0.f,i * 40.f });
				}
				else
				{
					fixedObstacle[i][j].setType(NONE);
					fixedObstacle[i][j].setPos({ (j - 20) * 40.f, 0.f, i * 40.f });
				}
			}
			else
				fixedObstacle[i][j].setType(0);
		}
	}
}

void gamingRander()
{
	gluLookAt(
		cameraPos.x, cameraPos.y, cameraPos.z,
		cameraAt.x, cameraAt.y, cameraAt.z,
		0.0, 1.0, 0.0);

	score = std::to_string((int)character.getPos().z / 40);

	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(character.getPos().x, character.getPos().y + 50, character.getPos().z);
	int len = (int)score.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score[i]);

	glPushMatrix();
	{
		glShadeModel(GL_SMOOTH);
		glPushMatrix();
		glColor3f(DiffuseLight[0], DiffuseLight[1], DiffuseLight[2]);
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
		glRotatef(-90, 1.0, 0.0, 0.0);
		glScalef(20.0, 20.0, 20.0);
		glutSolidCone(0.5, 1.0, 10, 10);
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

	}
	glPopMatrix();

	glPushMatrix();
	{
		character.draw();

		for (auto& v : CarArray)
			v.draw();

		for (int i = character.getPos().z / 40 - 10; i < character.getPos().z / 40 + 30; ++i)
		{
			if (fixedTileArray[i].getType() == RAIL)
				fixedTileArray[i].drawRail();
			else
				fixedTileArray[i].draw();
		}

		for (int i = 0; i < COL; ++i)
		{
			for (int j = 0; j < ROW; ++j)
			{
				if (character.getPos().z / 40 - fixedObstacle[i][j].getPos().z / 40 < 10 && character.getPos().z / 40 - fixedObstacle[i][j].getPos().z / 40 > -30)
					fixedObstacle[i][j].draw();
			}
		}
	}
	glPopMatrix();
}

void gamingUpdate()
{
	lightPos[0] = character.getPos().x + 10;
	lightPos[1] = character.getPos().y + 80;
	lightPos[2] = character.getPos().z + 50;


	// 카메라 캐릭터와의 거리와 비교해서 따라가기 
	if (!firstPerson) {

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
		// 왼쪽으로 따라가기
		if (MoveToCharX)
		{
			VECTOR3 temp = character.getPos();
			cameraPos.x += cameraMove * fabs(temp.x - cameraPos.x);
			cameraAt.x = cameraPos.x + 5;
			if (fabs(temp.x - cameraPos.x) < 20)
			{
				cameraPos.x = temp.x - 20;
				cameraAt.x = cameraPos.x + 5;
				MoveToCharX = false;
			}
		}

		// 카메라 자동이동 
		if (!finish)
		{
			cameraPos.z += 3.0;
			cameraAt.z = cameraPos.z + 20.f;
		}
	}
	else
	{
		cameraPos = character.getPos();
		cameraPos.y += 10;
		cameraPos.z += 150;
		cameraAt.x = cameraPos.x + firstPersonAt.x;
		cameraAt.z = cameraPos.z + 20;
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
			{
				finish = true;
				if (firstPerson)
				{
					cameraPos.x = character.getPos().x - 20;
					cameraPos.y = character.getPos().y + 60;
					cameraPos.z = character.getPos().z - 60;
					firstPerson = false;
				}
			}
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

			if (currenttime - fixedTileArray[i].getCMake() > fixedTileArray[i].getPeriod() && fixedTileArray[i].getType() == RAIL)
			{
				Car tempC1 = { {799.f *-fixedTileArray[i].getDirection() , 0.f, i * 40.f } };
				Car tempC2 = { {(799.f - 126.f) *-fixedTileArray[i].getDirection() , 0.f, i * 40.f } };
				tempC1.setVector(usingTrainVector);
				tempC2.setVector(usingTrainVector);
				tempC1.setSize({ 126 ,60, 40 });
				tempC2.setSize({ 126 ,60, 40 });
				tempC1.setSpeed(fixedTileArray[i].getCarSpeed());
				tempC2.setSpeed(fixedTileArray[i].getCarSpeed());
				tempC1.setDir();
				tempC2.setDir();
				CarArray.push_back(tempC1);
				CarArray.push_back(tempC2);
				fixedTileArray[i].setCMake(clock());
			}
		}
	}

}

void introInit()
{
	cameraPos = { 5.f, 10.f, 0.f };
	cameraAt = { 0, 5, -10 };

	crossy.loadPLY_X("resource/crossy.ply");
	crossy.setPos({ 0,0,0, });
}

void introRander()
{
	gluLookAt(
		cameraPos.x, cameraPos.y, cameraPos.z,
		cameraAt.x, cameraAt.y, cameraAt.z,
		0.0, 1.0, 0.0);

	glPushMatrix();
	{
		crossy.draw();
	}
	glPopMatrix();
}

void introUpdate()
{
	//currentScene = gaming;
}