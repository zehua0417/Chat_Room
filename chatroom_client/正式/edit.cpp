#include "edit.h"
extern HWND hwnd;

Edit::Edit(int x, int y, int w, int h, COLORREF color) :rect(x, y, w, h, color), cursor(x, y, 1, h - 4, color)
{
    this->inputState = false;
    this->textw = 0;
}


void Edit::Show()//��������
{
    rect.Show();//���λ���
    //��������
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    textw = textwidth(text.c_str());
    outtextxy(rect.GetX() + 10, rect.GetY() + 5, text.c_str());
    settextstyle(20, 0, "����");
    outtextxy(135, 100, "�˺ţ�");
    outtextxy(135, 200, "���룺");
    outtextxy(340, 277, "��¼");
    outtextxy(220, 277, "�˳�");
    //���
    if (inputState == true)
    {
        cursor.SetCurSor(rect.GetX() + textw + 10, rect.GetY() + 2);
        cursor.Show();
    }
}

void Edit::Show_chat()
{
    rect.Show();        //���λ���
    //��������
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);

    textw = textwidth(text.c_str());

    outtextxy(rect.GetX() + 10, rect.GetY() + 5, text.c_str());//�����ж�������е������Ƿ���

    settextstyle(20, 0, "����");
    rectangle(10, 600, 990, 800);//���öԻ���
    outtextxy(210, 840, "��Ч");
    outtextxy(360, 840, "����");
    outtextxy(500, 840, "����");


    //���
    if (inputState == true)
    {
        cursor.SetCurSor(rect.GetX() + textw + 10, rect.GetY() + 2);
        cursor.Show_chat();
    }
}

void Edit::ClickEvent(ExMessage msg)//�ж��Ƿ���
{
    //�ж�����Ƿ����˳���ť��   �����������ť
    if (msg.x >= 220 && msg.x < +220 + 40 && msg.y >= 275 &&
        msg.y <= 300 && msg.message == WM_LBUTTONDOWN) {

        MessageBox(hwnd, "��ȷ��Ҫ�˳���", "��ʾ", MB_OKCANCEL);//�����˳���
        exit(0);
    }
    //�ж�����Ƿ��ڵ�¼��ť����  ���������

}

bool Edit::InEdit(ExMessage msg)
{
    return rect.InRect(msg);
}

void Edit::OnEvent(ExMessage msg)//�������һЩ�޸�
{
    switch (msg.message)
    {
    case WM_LBUTTONDOWN:            //�����Ϣ
        if (InEdit(msg))
        {
            rect.SetColor(WHITE);
            inputState = true;      //����༭�򣬱༭״̬��Ϊ�ɱ༭״̬
        }
        else
        {
            rect.RestoreColor();    //��ԭ��ɫ
            inputState = false;
        }
        break;
    case WM_CHAR:                   //����������ַ���Ϣ
        if (inputState == true)     //һ���ǿ�����״̬
        {
            switch (msg.ch)
            {
            case '\b':              //ɾ��
                if (!text.empty())
                {
                    text.pop_back();    //�ַ���β��ɾ��
                }
                break;
            case '\r':                  //ȷ������
            case '\n':
                rect.RestoreColor();
                inputState = false;
                break;
            default:                    //�����ַ�
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
