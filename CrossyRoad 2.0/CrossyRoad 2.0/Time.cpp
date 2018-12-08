#include "Time.h"


Time::Time()
{
	priviousTime = clock();
}


Time::~Time()
{
}


float Time::update()
{
	currentTime = clock();
	frameTime = (currentTime - priviousTime) / 1000.0;
	priviousTime = currentTime;
	return frameTime;
}