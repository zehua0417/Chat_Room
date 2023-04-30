#pragma once
#include "cursor.h"
//HWND hwnd ;
class Edit//编辑类
{
public:
	Edit(int x, int y, int w, int h, COLORREF color);
	/*Edit(int x, int y, int w, int h, string text);*/
	void Show();//Show方法
	void ClickEvent(ExMessage msg);
	bool InEdit(ExMessage msg);
	void OnEvent(ExMessage msg);
	string GetText();
	int GetInt();
	int GetNum();
	void Show_chat();

private:
	Rect rect;
	Cursor cursor;
	string text;		//存储
	int textw;			//文字宽度
	bool inputState;	//是否输入
	
};

