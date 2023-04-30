#include "Client.h"

Client::Client(){
	m_hSock = socket(AF_INET, SOCK_STREAM, 0);
	m_port=9999;
	memset(&m_servAdr, 0, sizeof(m_servAdr));
	m_servAdr.sin_family = AF_INET;
	m_servAdr.sin_port = htons(m_port);
	inet_pton(AF_INET, "162.14.74.178", &m_servAdr.sin_addr);
}

Client::Client(unsigned int port){
	m_hSock=socket(AF_INET, SOCK_STREAM, 0) ;
	m_port=port;
	memset(&m_servAdr, 0, sizeof(m_servAdr));
	m_servAdr.sin_family = AF_INET;
	m_servAdr.sin_port = htons(m_port);
	inet_pton(AF_INET, "162.14.74.178", &m_servAdr.sin_addr);
}

Client::~Client() {
	closesocket(m_hSock);
}

bool Client::connect_ser() {
	if (connect(m_hSock, (SOCKADDR*)&m_servAdr, sizeof(m_servAdr)) == SOCKET_ERROR) {
		printf("connect error : %d", GetLastError());
		return 0;
	}else{
		//加上连接成功提示音
		return 1;
	}
}

unsigned Client::SendMsg(std::string input) {
	SOCKET sock = *((SOCKET*)&GetInstance()->m_hSock);
	//while(1){
		sprintf(Client::GetInstance()->m_szMsg,input.c_str());
		if (!strcmp(Client::GetInstance()->m_szMsg, "QUIT\n") || !strcmp(Client::GetInstance()->m_szMsg, "quit\n")) {
			closesocket(sock);
			exit(0);
		}
		send(sock, Client::GetInstance()->m_szMsg, strlen(Client::GetInstance()->m_szMsg), 0);
	//}
	return 0;
}

std::string Client::RecvMsg()
{
	SOCKET sock = *((SOCKET*)&GetInstance()->m_hSock);

	char msg[BUF_SIZE];
	//while (1) {
		int len = recv(sock, msg, sizeof(msg) - 1, 0);
		if (len == -1) {
			return{};
		}
		msg[len] = '\0';
		return std::string(msg);
	//}
	return{};
}

/*
void Client::start_chat() {
	connect_ser();
	HANDLE hSendHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendMsg, (void*)std::string, 0, NULL);
	HANDLE hRecvHand = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvMsg, (void*)&m_hSock, 0, NULL);
	WaitForSingleObject(hSendHand, INFINITE);
}
*/
