#include "Time.h"
#include <Windows.h>


Time::Time()
{
	priviouTime = GetTickCount();
}


Time::~Time()
{
}


float Time::update()
{
	currentTime = GetTickCount();
	frameTime = currentTime - priviouTime;
	priviouTime = currentTime;

	return frameTime;
}