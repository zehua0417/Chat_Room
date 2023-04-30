#include "edit.h"
extern HWND hwnd;

Edit::Edit(int x, int y, int w, int h, COLORREF color) :rect(x, y, w, h, color), cursor(x, y, 1, h - 4, color)
{
    this->inputState = false;
    this->textw = 0;
}


void Edit::Show()//绘制文字
{
    rect.Show();//矩形绘制
    //处理文字
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    textw = textwidth(text.c_str());
    outtextxy(rect.GetX() + 10, rect.GetY() + 5, text.c_str());
    settextstyle(20, 0, "楷体");
    outtextxy(135, 100, "账号：");
    outtextxy(135, 200, "密码：");
    outtextxy(340, 277, "登录");
    outtextxy(220, 277, "退出");
    //光标
    if (inputState == true)
    {
        cursor.SetCurSor(rect.GetX() + textw + 10, rect.GetY() + 2);
        cursor.Show();
    }
}

void Edit::Show_chat()
{
    rect.Show();        //矩形绘制
    //处理文字
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);

    textw = textwidth(text.c_str());

    outtextxy(rect.GetX() + 10, rect.GetY() + 5, text.c_str());//用于判断输入框中的文字是否换行

    settextstyle(20, 0, "楷体");
    rectangle(10, 600, 990, 800);//设置对话框
    outtextxy(210, 840, "音效");
    outtextxy(360, 840, "发送");
    outtextxy(500, 840, "返回");


    //光标
    if (inputState == true)
    {
        cursor.SetCurSor(rect.GetX() + textw + 10, rect.GetY() + 2);
        cursor.Show_chat();
    }
}

void Edit::ClickEvent(ExMessage msg)//判断是否点击
{
    //判断鼠标是否在退出按钮中   且左键单击按钮
    if (msg.x >= 220 && msg.x < +220 + 40 && msg.y >= 275 &&
        msg.y <= 300 && msg.message == WM_LBUTTONDOWN) {

        MessageBox(hwnd, "你确定要退出吗？", "提示", MB_OKCANCEL);//弹出退出框
        exit(0);
    }
    //判断鼠标是否在登录按钮里面  且左键单击

}

bool Edit::InEdit(ExMessage msg)
{
    return rect.InRect(msg);
}

void Edit::OnEvent(ExMessage msg)//对输入的一些修改
{
    switch (msg.message)
    {
    case WM_LBUTTONDOWN:            //鼠标消息
        if (InEdit(msg))
        {
            rect.SetColor(WHITE);
            inputState = true;      //点击编辑框，编辑状态改为可编辑状态
        }
        else
        {
            rect.RestoreColor();    //还原颜色
            inputState = false;
        }
        break;
    case WM_CHAR:                   //按键输入的字符消息
        if (inputState == true)     //一定是可输入状态
        {
            switch (msg.ch)
            {
            case '\b':              //删除
                if (!text.empty())
                {
                    text.pop_back();    //字符串尾部删除
                }
                break;
            case '\r':                  //确认输入
            case '\n':
                rect.RestoreColor();
                inputState = false;
                break;
            default:                    //其他字符
                text.push_back(msg.ch);
                break;
            }
        }
        break;
    }
}
string Edit::GetText()
{
    return text;
}
