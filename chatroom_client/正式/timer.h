#pragma once
#include"common.h"
class Timer//时间类
{
public:
	Timer(int duration, int id);
	bool OnTimer();
private:
	int id;
	int duration;//间隔期间
};

