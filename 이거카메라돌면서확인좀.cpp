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

class OBJECT
{

protected:
	vector<PLYINFO> info;
	VECTOR3 position; // push matrix ->������ ��ġ��ŭ translate �� ������ �׸��� ->popmatrix


public:
	OBJECT()
	{
		position = { 0,0,0 };
	}

	OBJECT(VECTOR3 vec)
	{
		position = vec;
	}

	void draw()
	{

		glBegin(GL_QUADS);
		for (auto iter : info)
		{
			glColor3f(iter.color.r, iter.color.g, iter.color.b);
			glVertex3i(iter.vec.x, iter.vec.y, iter.vec.z);
		}
		glEnd();
	}

	void loadPLY(string path)
	{

		char* exist = strstr((char*)path.c_str(), "ply");

		if (exist == NULL)
		{
			return;
		}

		else
		{
			FILE* file = fopen(path.c_str(), "r");

			if (file)//�дµ� ������ �ߴٸ�
			{
				cout << path.c_str() << endl;
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
					fgets(buffer, 300, file);//��� �Է��� �ް���?
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

};

//vector<PLYINFO> info;
//vector<PLYINFO> carinfo;

OBJECT chicken{ {50,0,0} };
OBJECT puplecar{ {-50,0,0} };

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

	chicken.loadPLY("chicken.ply");
	puplecar.loadPLY("puple car.ply");

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
		glPushMatrix();
		{
			chicken.draw();

		}
		glPopMatrix();

		glPushMatrix();
		{
			puplecar.draw();
		}
		glPopMatrix();
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

	glutTimerFunc(50, TimerFunction, 1);
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
