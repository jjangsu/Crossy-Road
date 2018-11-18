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

	// GenList ���� �Լ��� glutCreateWindow���Ŀ� �ҷ����� �Ѵ�.
	// �ȱ׷��� ����.
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

// ���α׷� ����: <Ctrl+F5> �Ǵ� [�����] > [��������� �ʰ� ����] �޴�
// ���α׷� �����: <F5> Ű �Ǵ� [�����] > [����� ����] �޴�

// ������ ���� ��: 
//   1. [�ַ�� Ž����] â�� ����Ͽ� ������ �߰�/�����մϴ�.
//   2. [�� Ž����] â�� ����Ͽ� �ҽ� ��� �����մϴ�.
//   3. [���] â�� ����Ͽ� ���� ��� �� ��Ÿ �޽����� Ȯ���մϴ�.
//   4. [���� ���] â�� ����Ͽ� ������ ���ϴ�.
//   5. [������Ʈ] > [�� �׸� �߰�]�� �̵��Ͽ� �� �ڵ� ������ ����ų�, [������Ʈ] > [���� �׸� �߰�]�� �̵��Ͽ� ���� �ڵ� ������ ������Ʈ�� �߰��մϴ�.
//   6. ���߿� �� ������Ʈ�� �ٽ� ������ [����] > [����] > [������Ʈ]�� �̵��ϰ� .sln ������ �����մϴ�.

