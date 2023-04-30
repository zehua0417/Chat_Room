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
	//构造函数, 同时绑定端口
	Client();
	Client(unsigned int port);
	~Client();
	static Client* GetInstance() {
		static Client client;
		return &client;
	}
	/**
	 * @brief 连接服务器
	 * @return 0 连接失败
	 *		   1 连接成功
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