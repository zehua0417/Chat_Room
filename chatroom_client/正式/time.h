#pragma once
#include "common.h"
class Timer
{
public:
	Timer(int duration, int id);
	bool OnTimer();
private:
	int id;
	int duration;
};