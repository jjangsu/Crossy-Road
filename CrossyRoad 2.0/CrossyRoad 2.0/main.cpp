#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <random>
#include <chrono>
#include <vector>
#include "Tile.h"

#include "global variable.h"
#include "Define.h"

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void spckeycallback(int key, int x, int y);



int main(int argc, char *argv[])
{
	srand((unsigned int)time(nullptr));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(width, height); // 윈도우의 크기 지정
	glutTimerFunc(1000 / 60, TimerFunction, 1); // 타이머 함수 설정 	

	glutCreateWindow("Corry Road"); // 윈도우 생성 (윈도우 이름)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // 출력 함수의 지정


	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);
	glutSpecialFunc(spckeycallback);

	character.loadPLY("resource/chicken.ply");
	character.setPos({ 0,0,0, });

	pupleCar.loadPLY("resource/puple car.ply");
	usingCarVector = pupleCar.getVector();

	miniCar.loadPLY("resource/blue mini car.ply");
	usingCarVector = miniCar.getVector();

	grass.loadPLY("resource/temproad.ply");
	usingRoadVector = grass.getVector();

	road.loadPLY("resource/grass.ply");
	usingGrassVector = road.getVector();
	
	
	for (int i = 0; i < COL; ++i) {	// z
		fixedTileArray[i].setPos({ 0, -1, i * 40 });
		int tempType = TrueOrFalse(rd) +1;
		if (tempType == GRASS)
		{
			fixedTileArray[i].setVector(usingGrassVector);
			fixedTileArray[i].setType(GRASS);
		}
		else if (tempType == ROAD)
		{
			fixedTileArray[i].setVector(usingRoadVector);
			fixedTileArray[i].setType(ROAD);
		}
		fixedTileArray[i].setCMake(clock());
		fixedTileArray[i].setPeriod(MakeCarPeriod(rd));
		fixedTileArray[i].setCarSpeed(carSpeedRange(rd));
		int tempdir = TrueOrFalse(rd);
		if(tempdir == 1)
		{
			//cout << "뭐다냐";
			fixedTileArray[i].setDirection(1);
		}
		else
		{
			fixedTileArray[i].setDirection(-1);
		}
		
	}
	//std::cout << "성공" << std::endl;
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


	glPushMatrix();
	{
		character.draw();
		//pupleCar.draw();
		for (auto& v : CarArray)
			v.draw();

		for (int i = 0; i < COL; ++i)
			fixedTileArray[i].draw();
	}
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
}

void TimerFunction(int value)
{
	// 카메라 자동이동 
	cameraPos.z += 1.0;
	cameraAt.z = cameraPos.z + 20.f;

	for(auto& v: CarArray)
		v.move();

	for (auto iter = CarArray.begin();iter != CarArray.end();)
	{
		if ((character.getPos().z - iter->getPos().z) / 40 > 20  || (iter->getPos().z - character.getPos().z) / 40 < -5)
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

	int charz = character.getPos().z / 40 ;
	clock_t currenttime = clock();

	//왜안만들어지지
	for (int i = charz - 20; i < charz + 20; ++i)
	{
		if (i >= 0)
		{
			//cout << i << endl;
			if (currenttime - fixedTileArray[i].getCMake() > fixedTileArray[i].getPeriod() && fixedTileArray[i].getType() != GRASS)
			{

				Car tempcar{ { 700 * -fixedTileArray[i].getDirection(), 0, i * 40 } };
				tempcar.setDir();
				tempcar.setVector(usingCarVector);
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
	gluPerspective(90.0, w / h, 0.1, 1000);
	glTranslated(0, 0, -200);
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
		break;

	case KEYRIGHT:
		temp = character.getPos();
		character.setPos({ temp.x - MOVEDISTANCE,temp.y,temp.z });
		character.setRotation({ 0, -90, 0 });
		break;
	}
}
