#include"logon_graph.h"

HWND hwnd;

void Music_reminder1()//普通提示音函数
{
	mciSendString("open music1.wav", 0, 0, 0);
	mciSendString("play music1.wav ", 0, 0, 0);
}
void music_reminder2()//（群主）特别关心提示音函数
{
	mciSendString("open music2.wav", 0, 0, 0);
	mciSendString("play music2.wav", 0, 0, 0);
}

void logon_graph() {

	//const string USER_ACCOUNT = "你是最棒的";			//用户登录账号测试用例
	//const string USER_PASSWORDS = "123678";			//用户登录密码测试用例
	/*hwnd=initgraph(640, 480);*/
	initgraph(640, 480);
	IMAGE logon_bk;
	loadimage(&logon_bk, "4.jpg", 640, 480);
	putimage(0, 0, &logon_bk);
	setbkcolor(RGB(238, 238, 238));
	//cleardevice();!!!!!!!!!!!!!!!!!!!!!!!!!
	settextcolor(BLACK);
	/*settextstyle(25, 0, L"楷体");*/
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
				//如果账号密码正确    pEdit1->GetText() ==wstring(USER_PASSWORDS)
				//pEdit1->GetText()== USER_ACCOUNT&&pEdit2->GetText()== USER_PASSWORDS
				//0==strcmp(wstring(pEdit1->GetText()), wstring(USER_ACCOUNT))
				//比较用户输入账号与密码知否正确
				if (log_in(pEdit1->GetText(),pEdit2->GetText())) {
					MessageBox(hwnd, "欢迎进入聊天室", "提示", MB_OKCANCEL);//跳转界面
					if (!Client::GetInstance()->connect_ser())
						return;
					chat_graph();
				}
				else {
					MessageBox(hwnd, "账号或密码错误", "错误提示", MB_OKCANCEL);
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

void chat_graph()//聊天界面绘制函数
{
	initgraph(800, 900);
	IMAGE logon_bk;
	loadimage(&logon_bk, "4.jpg", 800, 900);
	putimage(0, 0, &logon_bk);
	setbkcolor(RGB(238, 238, 238));
	settextcolor(BLACK);

	Edit* pEdit1 = new Edit(10, 600, 780, 200, RGB(238, 238, 238));//聊天输入框
	Edit* pEdit2 = new Edit(200, 834, 60, 30, RGB(238, 238, 238));//音效按钮
	Edit* pEdit3 = new Edit(350, 834, 60, 30, RGB(238, 238, 238));//发送按钮
	Edit* pEdit4 = new Edit(490, 834, 60, 30, RGB(238, 238, 238));//离开按钮
	outtextxy(10, 580, "输入框");
	rectangle(10, 10, 790, 580);
	outtextxy(10, 10, "聊天界面");
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
			if (msg.x >= 350 && msg.x <= 410 && msg.y >= 834 && msg.y <= 864 && msg.message == WM_LBUTTONDOWN) {//如果点击发送按钮则在聊天室内显示，并且刷新输入框
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
			if (msg.x >= 200 && msg.x <= 260 && msg.y >= 834 && msg.y <= 864 && msg.message == WM_LBUTTONDOWN) {//如果点击音效按钮则可以选择关闭音效和开启音效
				MessageBox(hwnd, "是否关闭提示音", "提示", MB_OKCANCEL);//此处可以弄个全局变量来决定用户是否开启或关闭提示音，if（）mciSendString("close BGM ", 0, 0, 0)，也可以直接写（是否开启/关闭提示音）
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