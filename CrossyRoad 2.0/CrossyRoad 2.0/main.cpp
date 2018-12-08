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

	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(WIDTH, HEIGHT); // �������� ũ�� ����
	glutTimerFunc(1000 / 60, TimerFunction, 1); // Ÿ�̸� �Լ� ���� 	

	glutCreateWindow("Corry Road"); // ������ ���� (������ �̸�)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // ��� �Լ��� ����


	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMouseFunc(Mouse);
	glutSpecialFunc(spckeycallback);

	fixedTileArray = new Tile[COL]; 

	// ĳ����
	character.loadPLY("resource/chicken.ply");
	character.setPos({ 0,0,0, });
	character.setSize(20);

	// ��
	pupleCar.loadPLY("resource/puple car.ply");
	usingCarVector = pupleCar.getVector();

	miniCar.loadPLY("resource/blue mini car.ply");
	usingMiniCarVector = miniCar.getVector();

	orangeCar.loadPLY("resource/orange car.ply");
	usingvehicleVector = orangeCar.getVector();

	taxi.loadPLY("resource/taxi.ply");
	usingTaxiVector = taxi.getVector();

	// Ÿ��
	grass.loadPLY("resource/temproad.ply");
	usingRoadVector = grass.getVector();

	road.loadPLY("resource/grass.ply");
	usingGrassVector = road.getVector();
	
	
	
	for (int i = 0; i < COL; ++i) {	// z
		fixedTileArray[i].setPos({ 0, -1, i * 40 });
		int tempType = TileType(rd) + 1;
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
		int tempdir = TileType(rd);
		if(tempdir == 1)
		{
			//cout << "���ٳ�";
			fixedTileArray[i].setDirection(1);
		}
		else
		{
			fixedTileArray[i].setDirection(-1);
		}
		
	}
	//std::cout << "����" << std::endl;
	glutMainLoop();
}
// ������ ��� �Լ�
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
		
		for (auto& v : CarArray)
			v.draw();

		for (int i = character.getPos().z/40 - 5; i < character.getPos().z / 40 + 30; ++i)
			fixedTileArray[i].draw();
	}
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value)
{
	// ī�޶� �ڵ��̵� 
	cameraPos.z += 1.0;
	cameraAt.z = cameraPos.z + 20.f;
	
	//update Car
	for(auto& v: CarArray)
		v.move();

	//Release Car
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

	//Making Car
	for (int i = charz - 20; i < charz + 20; ++i)
	{
		if (i >= 0)
		{
			if (currenttime - fixedTileArray[i].getCMake() > fixedTileArray[i].getPeriod() && fixedTileArray[i].getType() == ROAD)
			{
				Car tempcar{ { 700 * -fixedTileArray[i].getDirection(), 0, i * 40 } };
				tempcar.setDir();

				int tempType = carType(rd);
				if (tempType == CAR)
					tempcar.setVector(usingCarVector);
				else if (tempType == MINICAR)
					tempcar.setVector(usingMiniCarVector);
				else if (tempType == VEHICLE)
					tempcar.setVector(usingvehicleVector);
				else if (tempType == TAXI)
					tempcar.setVector(usingTaxiVector);

				tempcar.setSpeed(fixedTileArray[i].getCarSpeed());
				CarArray.push_back(tempcar);
				fixedTileArray[i].setCMake(clock());

			}
		}
	}

	//�浹üũ?
	for (auto& iter : CarArray)
	{
		if (abs(iter.getPos().z - character.getPos().z) <= 80)
		{
			int carx = iter.getPos().x;
			int carz = iter.getPos().z;
			int carsize = iter.getSize();
			int charx = character.getPos().x;
			int charz = character.getPos().z;
			int charsize = character.getSize();

			if (carx - carsize < charx + charsize && carz + carsize < charz - charsize
				&& carx + carsize > charx - charsize && carz - carsize > charz + charsize)
			{
				exit(1);
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
		// ī�޶� yȸ��
	case 'y':
		cameraAt.x += 10.0;
		break;
	case 'Y':
		cameraAt.x -= 10.0;
		break;
		// ī�޶� zȸ��
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
		//temp = Object.getPos();
		if (HEIGHT * (temp.z + MOVEDISTANCE) / (RIGHTEDGE * 1) > HEIGHT / 2) {
			int i = HEIGHT * (temp.z + MOVEDISTANCE) / (RIGHTEDGE * 1);
			cameraPos.z = temp.z + MOVEDISTANCE - 60;
			cameraAt.z = cameraPos.z + 20.f;
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
		break;

	case KEYRIGHT:
		temp = character.getPos();
		character.setPos({ temp.x - MOVEDISTANCE,temp.y,temp.z });
		character.setRotation({ 0, -90, 0 });
		break;
	}
}
