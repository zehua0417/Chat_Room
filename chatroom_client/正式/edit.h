#pragma once
#include "cursor.h"
//HWND hwnd ;
class Edit//�༭��
{
public:
	Edit(int x, int y, int w, int h, COLORREF color);
	/*Edit(int x, int y, int w, int h, string text);*/
	void Show();//Show����
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
	string text;		//�洢
	int textw;			//���ֿ��
	bool inputState;	//�Ƿ�����
	
};

