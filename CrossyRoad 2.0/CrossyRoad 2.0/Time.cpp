#include "Time.h"
#include <Windows.h>
#include <time.h>


Time::Time()
{
	priviouTime = clock();
}


Time::~Time()
{
}


float Time::update()
{
	currentTime = clock();
	frameTime = currentTime - priviouTime;
	priviouTime = currentTime;
	return frameTime;
}