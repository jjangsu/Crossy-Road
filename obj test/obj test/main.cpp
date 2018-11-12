#pragma once
#include <gl/glut.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include "ObjLoader.h"

#define KEY_ESCAPE 27

using namespace std;

ObjLoader* loader;

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glLoadIdentity();

	loader->Create_Model();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESCAPE:
		exit(0);
		break;

	case 'a':
		loader->Rotate(1);
		break;

	case 'd':
		loader->Rotate(-1);
		break;

	case 'q':
		loader->Scale(-0.5);
		break;
	case 'e':
		loader->Scale(0.5);
		break;

	case 'w':
		loader->Move(0, 1);
		break;

	case 's':
		loader->Move(0, -1);
		break;

	default:
		break;
	}
}

void MyReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		cout << "Error!! : Please write file path" << endl;
		//return 0;
	}
	else
	{
		cout << "Obj File Open" << endl;
		cout << "W / S : Move model up / down" << endl;
		cout << "A / D : Rotate left / right" << endl;
		cout << "Q / E : Scale up / down" << endl;
		cout << "ESC   : Exit Program" << endl;
	}

	// initialize and run program
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Computer Graphics Obj Loader");

	glutReshapeFunc(MyReshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);

	// GenList 등의 함수는 glutCreateWindow이후에 불러져야 한다.
	// 안그러면 에러.
	loader = new ObjLoader();
	//loader->Open_ObjFile(argv[1]);
	//loader->Open_ObjFile("character object/box.obj");
	loader->Open_ObjFile("character object/chicken.obj");

	glutMainLoop();

	//system("pause")

	delete loader;
	return 0;
}
