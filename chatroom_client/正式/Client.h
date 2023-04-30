#define _CRT_SECURE_NO_WARNINGS
#include<Winsock2.h>
#include <Ws2tcpip.h>
#include <Windows.h>
#include <cstdio>
#include<string>
#pragma comment(lib,"Ws2_32.lib")
#define BUF_SIZE 1024



#ifndef CLIENT_H
#define CLIENT_H

class Client {
private:
	SOCKET m_hSock;
	SOCKADDR_IN m_servAdr;
	int m_port;
	char m_szMsg[BUF_SIZE];
public:
	//���캯��, ͬʱ�󶨶˿�
	Client();
	Client(unsigned int port);
	~Client();
	static Client* GetInstance() {
		static Client client;
		return &client;
	}
	/**
	 * @brief ���ӷ�����
	 * @return 0 ����ʧ��
	 *		   1 ���ӳɹ�
	 */
	bool connect_ser();

	/**
	 *
	 */
	static unsigned SendMsg(std::string input);
	static std::string RecvMsg();
	void start_chat();


};

#endif