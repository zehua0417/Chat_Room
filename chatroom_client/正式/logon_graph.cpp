#include"logon_graph.h"

HWND hwnd;

void Music_reminder1()//��ͨ��ʾ������
{
	mciSendString("open music1.wav", 0, 0, 0);
	mciSendString("play music1.wav ", 0, 0, 0);
}
void music_reminder2()//��Ⱥ�����ر������ʾ������
{
	mciSendString("open music2.wav", 0, 0, 0);
	mciSendString("play music2.wav", 0, 0, 0);
}

void logon_graph() {

	//const string USER_ACCOUNT = "���������";			//�û���¼�˺Ų�������
	//const string USER_PASSWORDS = "123678";			//�û���¼�����������
	/*hwnd=initgraph(640, 480);*/
	initgraph(640, 480);
	IMAGE logon_bk;
	loadimage(&logon_bk, "4.jpg", 640, 480);
	putimage(0, 0, &logon_bk);
	setbkcolor(RGB(238, 238, 238));
	//cleardevice();!!!!!!!!!!!!!!!!!!!!!!!!!
	settextcolor(BLACK);
	/*settextstyle(25, 0, L"����");*/
	Edit* pEdit1 = new Edit(200, 100, 200, 25, RGB(238, 238, 238));
	Edit* pEdit2 = new Edit(200, 200, 200, 25, RGB(238, 238, 238));
	Edit* pEdit3 = new Edit(340, 275, 40, 25, RGB(238, 238, 238));
	Edit* pEdit4 = new Edit(220, 275, 40, 25, RGB(238, 238, 238));
	ExMessage msg;
	//Edit edit();
	BeginBatchDraw();
	while (true)
	{

		while (peekmessage(&msg))
		{
			pEdit1->OnEvent(msg);
			pEdit2->OnEvent(msg);
			if (msg.x >= 340 && msg.x <= (340 + 40) && msg.y >= 275 &&
				msg.y <= 300 && msg.message == WM_LBUTTONDOWN) {
				//����˺�������ȷ    pEdit1->GetText() ==wstring(USER_PASSWORDS)
				//pEdit1->GetText()== USER_ACCOUNT&&pEdit2->GetText()== USER_PASSWORDS
				//0==strcmp(wstring(pEdit1->GetText()), wstring(USER_ACCOUNT))
				//�Ƚ��û������˺�������֪����ȷ
				if (log_in(pEdit1->GetText(),pEdit2->GetText())) {
					MessageBox(hwnd, "��ӭ����������", "��ʾ", MB_OKCANCEL);//��ת����
					if (!Client::GetInstance()->connect_ser())
						return;
					chat_graph();
				}
				else {
					MessageBox(hwnd, "�˺Ż��������", "������ʾ", MB_OKCANCEL);
				}
			}
			pEdit3->ClickEvent(msg);
			pEdit4->ClickEvent(msg);
		}

		pEdit1->Show();
		pEdit2->Show();
		pEdit3->Show();
		pEdit4->Show();
		FlushBatchDraw();
	}
	EndBatchDraw();
	closegraph();
}

void chat_graph()//���������ƺ���
{
	initgraph(800, 900);
	IMAGE logon_bk;
	loadimage(&logon_bk, "4.jpg", 800, 900);
	putimage(0, 0, &logon_bk);
	setbkcolor(RGB(238, 238, 238));
	settextcolor(BLACK);

	Edit* pEdit1 = new Edit(10, 600, 780, 200, RGB(238, 238, 238));//���������
	Edit* pEdit2 = new Edit(200, 834, 60, 30, RGB(238, 238, 238));//��Ч��ť
	Edit* pEdit3 = new Edit(350, 834, 60, 30, RGB(238, 238, 238));//���Ͱ�ť
	Edit* pEdit4 = new Edit(490, 834, 60, 30, RGB(238, 238, 238));//�뿪��ť
	outtextxy(10, 580, "�����");
	rectangle(10, 10, 790, 580);
	outtextxy(10, 10, "�������");
	ExMessage msg;
	Edit edit();

	BeginBatchDraw();
	int i = 0;
	std::thread t([&i]() {
		while (1) {
			outtextxy(10, 20 + (i++) * GAP, Client::GetInstance()->RecvMsg().c_str());
		}
	});
	while (1) {
		while (peekmessage(&msg)){
			pEdit1->OnEvent(msg);
			if (msg.x >= 350 && msg.x <= 410 && msg.y >= 834 && msg.y <= 864 && msg.message == WM_LBUTTONDOWN) {//���������Ͱ�ť��������������ʾ������ˢ�������
				if (i <= 27) {
					std::string sendmsg =pEdit1->GetText();
					Client::SendMsg(sendmsg);
					std::string showmsg = std::string("[you]: ") + sendmsg;
					outtextxy(10, 20 + i * GAP, (showmsg).c_str());
					//pEdit1->GetText();

					rectangle(10, 10, 790, 580);
				}
				i++;
			}
			if (msg.x >= 200 && msg.x <= 260 && msg.y >= 834 && msg.y <= 864 && msg.message == WM_LBUTTONDOWN) {//��������Ч��ť�����ѡ��ر���Ч�Ϳ�����Ч
				MessageBox(hwnd, "�Ƿ�ر���ʾ��", "��ʾ", MB_OKCANCEL);//�˴�����Ū��ȫ�ֱ����������û��Ƿ�����ر���ʾ����if����mciSendString("close BGM ", 0, 0, 0)��Ҳ����ֱ��д���Ƿ���/�ر���ʾ����
			}
			if (msg.x >= 490 && msg.x <= 550 && msg.y >= 834 && msg.y <= 864 && msg.message == WM_LBUTTONDOWN) {
				logon_graph();
			}
			pEdit3->ClickEvent(msg);
			pEdit4->ClickEvent(msg);
		}
		pEdit1->Show_chat();
		pEdit2->Show_chat();
		pEdit3->Show_chat();
		pEdit4->Show_chat();
		FlushBatchDraw();
	}


	EndBatchDraw();
	closegraph();

}