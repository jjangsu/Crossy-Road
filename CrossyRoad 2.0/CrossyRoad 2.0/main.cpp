#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
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

	chicken.loadPLY("resource/chicken.ply");
	chicken.setRotation({ 0, 180, 0 });
	chicken.setPos({ 0,0,0, });
	pupleCar.loadPLY("resource/puple car.ply");
	grass.loadPLY("resource/temproad.ply");
	usingGrassVector = grass.getVector();

	//objVectorContainer.push_back(grass);

	for (int i = 0; i < ROW; ++i)  // x
		for (int j = 0; j < COL; ++j){	// z
			fixedTileArray[i][j].setPos({ i* 40, -1, -j * 40 });
			fixedTileArray[i][j].setVector(usingGrassVector);
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
		
		chicken.draw();
		pupleCar.draw();

		for (int i = 0; i < COL; ++i)
			for (int j = 0; j < ROW; ++j)
				fixedTileArray[i][j].draw();
	}
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	
	switch (key)
	{
	case 'w':
		cameraAt.y += 10.0;
		cameraPos.y += 10.0;
		break;
	case 's':
		cameraAt.y -= 10.0;
		cameraPos.y -= 10.0;
		break;
	case 'a':
		cameraAt.x -= 10.0;
		cameraPos.x -= 10.0;
		break;
	case 'd':
		cameraAt.x += 10.0;
		cameraPos.x += 10.0;
		break;
	case 'e':
		cameraAt.z += 10.0;
		cameraPos.z += 10.0;
		break;
	case 'q':
		cameraAt.z -= 10.0;
		cameraPos.z -= 10.0;
		break;
	case 'x':
		cameraAt.y += 10.0;
		break;
	case 'X':
		cameraAt.y -= 10.0;
		break;
		// ī�޶� yȸ��
	case 'y':
		cameraAt.x -= 10.0;
		break;
	case 'Y':
		cameraAt.x += 10.0;
		break;
		// ī�޶� zȸ��
	case 'z':
		cameraAt.z += 10.0;
		break;
	case 'Z':
		cameraAt.z -= 10.0;

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
		temp = chicken.getPos();
		chicken.setPos({ temp.x,temp.y,temp.z - MOVEDISTANCE });
		break;

	case KEYDOWN:
		temp = chicken.getPos();
		chicken.setPos({ temp.x,temp.y,temp.z + MOVEDISTANCE });
		break;

	case KEYLEFT:
		temp = chicken.getPos();
		chicken.setPos({ temp.x - MOVEDISTANCE,temp.y,temp.z });
		break;

	case KEYRIGHT:
		temp = chicken.getPos();
		chicken.setPos({ temp.x + MOVEDISTANCE,temp.y,temp.z });
		break;
	}
}
