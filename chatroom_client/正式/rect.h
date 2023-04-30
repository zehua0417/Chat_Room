#pragma once
#include "common.h"
class Rect
{
public:
	Rect(int x = 0, int y = 0, int w = EDIT_W, int h = EDIT_H, COLORREF = RGB(238, 238, 238));
	int GetX();//getset方法
	int GetY();
	int GetW();
	int GetH();
	int GetColor();
	void SetColor(COLORREF color);
	void SetX(int x);
	void SetY(int y);
	void SetW(int w);
	void SetH(int h);
	void RestoreColor();//还原颜色！！！！！！！！
	void Show();//矩形框的展示方法，规定颜色，字体，方框大小
	bool InRect(ExMessage msg);//判断鼠标是否在矩形框中，鼠标在框中返回true
private:
	int x;
	int y;
	int w;
	int h;
	COLORREF curColor;//当前颜色
	COLORREF oldColor;//过去颜色
};
