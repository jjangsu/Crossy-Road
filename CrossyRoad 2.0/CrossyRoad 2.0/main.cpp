#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <vector>

#include "Struct.h"
#include "Object.h"

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);





//vector<PLYINFO> info;
//vector<PLYINFO> carinfo;

Object chicken{ {50,0,0} };
Object puplecar{ {-50,0,0} };
Object grass{ {50,0,-1} };

vector<Object> objVectorContainer;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸� �Լ� ���� 	

	glutCreateWindow("Corry Road"); // ������ ���� (������ �̸�)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutMouseFunc(Mouse);

	chicken.loadPLY("resource/chicken.ply");
	puplecar.loadPLY("resource/puple car.ply");
	grass.loadPLY("resource/grass.ply");

	objVectorContainer.push_back(chicken);
	objVectorContainer.push_back(puplecar);
	objVectorContainer.push_back(grass);
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	{
		glRotatef(-90.f, 1.0, 0.0, 0.0);
		for (auto iter : objVectorContainer)
		{
			iter.draw();
		}
	}
	glPopMatrix();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	gluLookAt(0, 100, 0, 0, 0, 0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, w / h, 1, 1000);
	glTranslated(0, -50, -300);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 0);
	glLoadIdentity();
}

void TimerFunction(int value)
{

	glutTimerFunc(500, TimerFunction, 1);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(1);
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

}