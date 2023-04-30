#include "edit.h"
#include"logon_graph.h"
int main(void)
{
	//初始化socket环境
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}

	//Client::GetInstance()->connect_ser();
	logon_graph();
	

	WSACleanup();
	return 0;
}
