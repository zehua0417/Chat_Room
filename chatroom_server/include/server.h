#ifndef SERVER_H
#define SERVER_H

#include"../include/header.h"
/**
 * @brief 用于保存客户端用户信息
 */
class Client{
public:
    int m_sockfd;
    std::string m_name;
};

/**
 * @brief 服务器类
 */
class Server{
public:
    const unsigned int m_port;
    int m_epld;
    int m_sockfd;
    struct sockaddr_in m_addr;
    struct epoll_event m_ev;
    struct epoll_event m_ev_client;
    struct epoll_event m_evs[MAX_CONNECT];
    int m_ret;
    std::map<int,Client> m_clients;
//public:
    Server();
    Server(unsigned int port);
    int init_epoll();
    int start_epoll();

};

#endif