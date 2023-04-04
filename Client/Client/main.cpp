/**
 * ������:
 * ip:162.14.74.178
 * user: guest, passwd: helloworld(��Ȩ��)
 * user: lihua, passwd: lizehua21(��Ȩ��)
 * user: root, passwd: 030316
 * wd: /home/lihau/project/chatroom_server/
 */
#define _CRT_SECURE_NO_WARNINGS 
#include<Winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib,"Ws2_32.lib")
#define BUF_SIZE 1024

char szMsg[BUF_SIZE];

unsigned SendMsg(void* arg) 
{
	SOCKET sock = *((SOCKET*)arg);
	while (1) 
	{
		scanf("%s", szMsg);
		if (!strcmp(szMsg, "QUIT\n") || !strcmp(szMsg, "quit\n"))
		{
			closesocket(sock);
			exit(0);
		}
		send(sock, szMsg, strlen(szMsg), 0);
	}
	return 0;
}
unsigned RecvMsg(void* arg) 
{
	SOCKET sock = *((SOCKET*)arg);

	char msg[BUF_SIZE];
	while (1)
	{
		int len = recv(sock, msg, sizeof(msg) - 1, 0);
		if (len == -1)
		{
			return -1;
		}
		msg[len] = '\0';
		printf("%s\n", msg);

	}
	return 0;
}

int main(void) {
	//��ʼ��socket����
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
//======================================================================
	//����socket
	SOCKET hSock;
	hSock = socket(AF_INET, SOCK_STREAM, 0);

	//�󶨶˿�
	SOCKADDR_IN servAdr;
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_port = htons(9999);
	inet_pton(AF_INET, "162.14.74.178", &servAdr.sin_addr);

	//���ӷ�����
	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)// ! ���������������� 
	{
		printf("connect error : %d", GetLastError());
		return -1;
	}else {
		printf("��ӭ�㣬�ҵ����ѡ���������������û�����");
		//�������ӳɹ���ʾ��
	}

	//ѭ������Ϣ
	HANDLE hSendHand = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) SendMsg,(void*)&hSock, 0, NULL);
	
	//ѭ������Ϣ
	HANDLE hRecvHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvMsg, (void*)&hSock, 0, NULL);
	
	//�ȴ��߳̽���

	WaitForSingleObject(hSendHand, INFINITE);
	closesocket(hSock);
	WSACleanup();
	return 0;
}