#pragma once
#include "common.h"
class Rect
{
public:
	Rect(int x = 0, int y = 0, int w = EDIT_W, int h = EDIT_H, COLORREF = RGB(238, 238, 238));
	int GetX();//getset����
	int GetY();
	int GetW();
	int GetH();
	int GetColor();
	void SetColor(COLORREF color);
	void SetX(int x);
	void SetY(int y);
	void SetW(int w);
	void SetH(int h);
	void RestoreColor();//��ԭ��ɫ����������������
	void Show();//���ο��չʾ�������涨��ɫ�����壬�����С
	bool InRect(ExMessage msg);//�ж�����Ƿ��ھ��ο��У�����ڿ��з���true
private:
	int x;
	int y;
	int w;
	int h;
	COLORREF curColor;//��ǰ��ɫ
	COLORREF oldColor;//��ȥ��ɫ
};
