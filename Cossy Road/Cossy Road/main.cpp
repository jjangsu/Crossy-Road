#include "App.h"

GLFWwindow* window;

int main(int argc, char* argv[])
{
	char name[] = "CRORRY ROAD";
	App* app = App::create();
	//app->initialize(100, 100, 800, 600, name);
	app->initialize(100, 100, 800, 600, name);

	return app->run();
}