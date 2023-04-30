#pragma once
#include "rect.h"
#include "timer.h"
class Cursor
{
public:
	Cursor(int x, int y, int w, int h, COLORREF color);
	void Show();
	void Show_chat();
	void SetCurSor(int x, int y);
private:
	void Draw();
	void Draw_chat();
	void Clear();
	void Clear_chat();
private:

	Rect cursor;
	Timer timer;
	int count;			//¿ØÖÆ»æÖÆ
};

