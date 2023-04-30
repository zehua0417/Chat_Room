#include "cursor.h"
Cursor::Cursor(int x, int y, int w, int h, COLORREF color) :cursor(x, y, w, h, color),timer(20, 0)//cursor,timer初始化,构造方法
{
	count = 0;
}
void Cursor::Show()
{
	if (timer.OnTimer())
	{
		count++;			//用计数来控制绘制还是擦除
	}
	Draw();
	Clear();
}

void Cursor::Show_chat()
{
	if (timer.OnTimer())
	{
		count++;			//用计数来控制绘制还是擦除
	}
	Draw_chat();
	Clear_chat();
}

void Cursor::Draw()//绘制矩形框
{
	if (count % 60 < 30)
	{
		setfillcolor(BLACK);
		rectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), cursor.GetY() + cursor.GetH());
	}
}

void Cursor::Draw_chat()//绘制矩形框
{
	if (count % 60 < 30)
	{
		setfillcolor(BLACK);
		rectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), cursor.GetY() + 25);
	}
}

void Cursor::Clear()//擦除矩形框
{
	if (count % 60 > 30)
	{
		//setfillcolor(WHITE);
		clearrectangle(cursor.GetX(), cursor.GetY(),
			cursor.GetX() + cursor.GetW(), cursor.GetY() + cursor.GetH());
	}
}

void Cursor::Clear_chat()//擦除矩形框
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
