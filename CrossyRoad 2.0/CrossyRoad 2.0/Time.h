#pragma once

class Time
{
	float currentTime;
	float priviouTime;
	float frameTime;
public:
	Time();
	~Time();

	float update();

};

