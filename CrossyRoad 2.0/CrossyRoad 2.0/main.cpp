#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
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
	glutInitWindowSize(width, height); // �������� ũ�� ����
	glutTimerFunc(1000 / 60, TimerFunction, 1); // Ÿ�̸� �Լ� ���� 	

	glutCreateWindow("Corry Road"); // ������ ���� (������ �̸�)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // ��� �Լ��� ����


	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMouseFunc(Mouse);
	glutSpecialFunc(spckeycallback);

	character.loadPLY("resource/chicken.ply");
	
	character.setPos({ 0,0,0, });
	pupleCar.loadPLY("resource/blue mini car.ply");
	usingCarVector = pupleCar.getVector();

	grass.loadPLY("resource/temproad.ply");
	usingRoadVector = grass.getVector();

	road.loadPLY("resource/grass.ply");
	usingGrassVector = road.getVector();
	

	std::uniform_int_distribution<int> uid(0, 1);
	std::default_random_engine dre(std::chrono::steady_clock::now().time_since_epoch().count());

	for (int i = 0; i < PUPLE_NUM; ++i) {
		fixedCarArray[i].setPos({-500 + 1000 * uid(dre), 0, i * 40 });
		fixedCarArray[i].setDir();
		fixedCarArray[i].setVector(usingCarVector);
	}
	for (int i = 0; i < COL; ++i) {	// z
		fixedTileArray[i].setPos({ 0, -1, i * 40 });
		int tempType = rand() % 2 +1;
		if (tempType == GRASS)
		{
			fixedTileArray[i].setVector(usingGrassVector);
		}
		else if (tempType == ROAD)
		{
			fixedTileArray[i].setVector(usingRoadVector);
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
		//pupleCar.draw();
		for (auto& v : fixedCarArray)
			v.draw();

		for (int i = 0; i < COL; ++i)
			fixedTileArray[i].draw();
	}
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value)
{
	for(auto& v: fixedCarArray)
		v.move();
	

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
