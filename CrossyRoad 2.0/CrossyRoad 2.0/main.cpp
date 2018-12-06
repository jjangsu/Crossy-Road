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
		
		chicken.draw();
		pupleCar.draw();

		for (int i = 0; i < COL; ++i)
			for (int j = 0; j < ROW; ++j)
				fixedTileArray[i][j].draw();
	}
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기
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
		// 카메라 y회전
	case 'y':
		cameraAt.x -= 10.0;
		break;
	case 'Y':
		cameraAt.x += 10.0;
		break;
		// 카메라 z회전
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
