#pragma once
#include <time.h>
class Time
{
	clock_t currentTime;
	clock_t priviousTime;
	float frameTime;
public:
	Time();
	~Time();

	float update();

};

