#include "cursor.h"
Cursor::Cursor(int x, int y, int w, int h, COLORREF color) :cursor(x, y, w, h, color),timer(20, 0)//cursor,timer��ʼ��,���췽��
{
	count = 0;
}
void Cursor::Show()
{
	if (timer.OnTimer())
	{
		count++;			//�ü��������ƻ��ƻ��ǲ���
	}
	Draw();
	Clear();
}

void Cursor::Show_chat()
{
	if (timer.OnTimer())
	{
		count++;			//�ü��������ƻ��ƻ��ǲ���
	}
	Draw_chat();
	Clear_chat();
}

void Cursor::Draw()//���ƾ��ο�
{
	if (count % 60 < 30)
	{
		setfillcolor(BLACK);
		rectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), cursor.GetY() + cursor.GetH());
	}
}

void Cursor::Draw_chat()//���ƾ��ο�
{
	if (count % 60 < 30)
	{
		setfillcolor(BLACK);
		rectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), cursor.GetY() + 25);
	}
}

void Cursor::Clear()//�������ο�
{
	if (count % 60 > 30)
	{
		//setfillcolor(WHITE);
		clearrectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), cursor.GetY() + cursor.GetH());
	}
}

void Cursor::Clear_chat()//�������ο�
{
	if (count % 60 > 30)
	{
		//setfillcolor(WHITE);
		clearrectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), (cursor.GetY() + 25));
	}
}

void Cursor::SetCurSor(int x, int y)
{
	cursor.SetX(x);
	cursor.SetY(y);

}
