#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


struct COLOR
{
	float r;
	float g;
	float b;
};


struct VECTOR2
{
	int x;
	int y;
};

struct VECTOR3
{
	int x;
	int y;
	int z;
};

struct PLYINFO
{
	COLOR color;
	VECTOR3 vec;
};

vector<PLYINFO> info;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void TimerFunction(int value);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);

void loadPLY(string path, vector<PLYINFO>& info)
{

	char* exist = strstr((char*)path.c_str(), "ply");

	if (exist == NULL)
	{
		return;
	}

	else
	{
		FILE* file = fopen(path.c_str(), "r");

		if (file)//읽는데 성공을 했다면
		{
			char buffer[300];
			int numofvertex;
			while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
			{
				fgets(buffer, 300, file);			// format
			}
			strcpy(buffer, buffer + strlen("element vertex"));
			sscanf(buffer, "%i", &numofvertex);

			cout << numofvertex << endl;

			while (strncmp("end_header", buffer, strlen("end_header")) != 0)
			{
				//system("pause");
				fgets(buffer, 300, file);//계속 입력을 받겠죠?
			}


			PLYINFO temp;
			for (int i = 0; i < numofvertex; ++i)
			{
				fgets(buffer, 300, file);
				sscanf(buffer, "%d %d %d %f %f %f", &temp.vec.x, &temp.vec.y, &temp.vec.z, &temp.color.r, &temp.color.g, &temp.color.b);
				temp.color.r = temp.color.r / 255.0;
				temp.color.g = temp.color.g / 255.0;
				temp.color.b = temp.color.b / 255.0;
				info.push_back(temp);
			}

			cout << "-------------------------------------------------------------------------------------------" << endl;

		}
	}
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutTimerFunc(50, TimerFunction, 1); // 타이머 함수 설정 	

	glutCreateWindow("1-16"); // 윈도우 생성 (윈도우 이름)
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutMouseFunc(Mouse);
	loadPLY("chicken.ply", info);
	glutMainLoop();
}
// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);	glLoadIdentity();
	glPushMatrix();
	glTranslated(3.0, 0.0, 0.0);
	//glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	for (auto iter : info)
	{
		glColor3f(iter.color.r, iter.color.g, iter.color.b);
		//cout << iter.color.r;
		glVertex3i(iter.vec.x, iter.vec.y, iter.vec.z);
	}
	glEnd();	glPopMatrix();
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
	
	glutTimerFunc(300, TimerFunction, 1);
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

}
