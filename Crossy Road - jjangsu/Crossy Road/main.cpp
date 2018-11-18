#include "stdafx.h"

void display();
void MyReshape(int width, int height);
void keyboard(unsigned char key, int x, int y);

ObjLoader* chicken;


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
	glutCreateWindow("Cossy Road");

	glutReshapeFunc(MyReshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);

	// GenList 등의 함수는 glutCreateWindow이후에 불러져야 한다.
	// 안그러면 에러.
	//loader->Open_ObjFile(argv[1]);
	//loader->Open_ObjFile("character object/box.obj");
	chicken = new ObjLoader();
	chicken->Open_ObjFile("resource/character object/chicken.obj");

	glutMainLoop();

	//system("pause")

	delete chicken;
	return 0;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case KEY_ESCAPE:
		exit(0);
		break;

	case 'a':
		chicken->Rotate(1);
		break;

	case 'd':
		chicken->Rotate(-1);
		break;

	case 'q':
		chicken->Scale(-0.5);
		break;
	case 'e':
		chicken->Scale(0.5);
		break;

	case 'w':
		chicken->Move(0, 1);
		break;

	case 's':
		chicken->Move(0, -1);
		break;

	default:
		break;
	}
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();

	chicken->draw();

	glutSwapBuffers();
}

void MyReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

