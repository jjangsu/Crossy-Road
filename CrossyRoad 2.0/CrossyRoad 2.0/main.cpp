#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <vector>

#include "Struct.h"
#include "Object.h"
#include "global variable.h"

using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);






//vector<PLYINFO> info;
//vector<PLYINFO> carinfo;




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

	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutTimerFunc(50, TimerFunction, 1); // 타이머 함수 설정 	

	glutCreateWindow("Corry Road"); // 윈도우 생성 (윈도우 이름)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // 출력 함수의 지정

	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);

	chicken.loadPLY("resource/chicken.ply");
	puplecar.loadPLY("resource/puple car.ply");
	grass.loadPLY("resource/grass.ply");

	objVectorContainer.push_back(chicken);
	objVectorContainer.push_back(puplecar);
	objVectorContainer.push_back(grass);
	glutMainLoop();
}
// 윈도우 출력 함수
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

	glutSwapBuffers(); // 화면에 출력하기
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
