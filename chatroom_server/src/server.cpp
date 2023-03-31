#include"../include/header.h"
#include"../include/server.h"

Server::Server():m_port(9159){};
Server::Server(unsigned int port):m_port(port){};//安全性漏洞, 但是问题不大

int Server::init_epoll(){
    //创建epoll实例
    m_epld = epoll_create1(0);
    if(m_epld < 0){
        perror("epoll creat error\n");
        return -1;
    }

    //创建用于监听的socket
    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sockfd < 0){
        perror("socket creat error\n");
        return -1;
    }

    //绑定本地的ip和端口
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_addr.sin_port = htons(m_port);

    m_ret = bind(m_sockfd, (struct sockaddr*)&m_addr, sizeof(m_addr));
    if(m_ret < 0){
        perror("bind error\n");
        return -1;
    }

    //监听Client
    listen(m_sockfd, MAX_CONNECT);
    if(m_ret < 0){
        perror("listen error\n");
        return -1;
    }

    return 0;
}


int Server::start_epoll(){
    m_ev.events = EPOLLIN;
    m_ev.data.fd = m_sockfd;

    m_ret = epoll_ctl(m_epld, EPOLL_CTL_ADD, m_sockfd, &m_ev);
    if(m_ret < 0){
        perror("epoll_ctl error\n");
        return -1;
    }

    //开始循环监听客户端
    while(1){
        int n = epoll_wait(m_epld, m_evs, MAX_CONNECT, -1);

        if(n < 0){
            perror("epoll_wait erreo\n");
            return -1;
        }

        for(int i = 0; i < n; ++i){
            int fd = m_evs[i].data.fd;
            //如果是监听的fd收到消息, 表示有客户端进行连接了
            if(fd == m_sockfd){
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int client_sockfd = accept(m_sockfd, (struct sockaddr*) &client_addr, &client_addr_len);
                if(client_sockfd < 0){
                    perror("connect error");
                    return -1;
                }

                //将客户端的socket接入epoll
                m_ev_client.events = EPOLLIN; //检测客户端消息
                m_ev_client.data.fd = client_sockfd; //
                m_ret = epoll_ctl(m_epld, EPOLL_CTL_ADD, client_sockfd, &m_ev_client);
                if(m_ret < 0){
                    perror("epoll_ctl(ev_client) error\n");
                    return -1;
                }
                printf("%d正在连接...\n",client_addr.sin_addr.s_addr);

                //保存客户端信息
                Client client;
                client.m_sockfd = client_sockfd;
                client.m_name = "";
                m_clients[client_sockfd] = client;
            }else{//有消息过来
                char buffer[TXT_SIZE];
                int txt_length = read(fd,buffer,TXT_SIZE);
                if(txt_length < 0){
                    perror("txt length < 0\n");
                    return -1;
                }else if(txt_length == 0){
                    //断开连接
                    close(fd);
                    epoll_ctl(m_epld, EPOLL_CTL_DEL, fd, 0);
                    m_clients.erase(fd);
                }else{
                    std::string msg(buffer, n);
                    if(m_clients[fd].m_name == ""){//如果姓名为空, 说明该消息为用户名
                        m_clients[fd].m_name = msg;
                    }else{//消息为聊天消息
                        std::string name = m_clients[fd].m_name;
                        for(auto &c:m_clients){
                            if(c.first != fd){
                                write(c.first, ('[' + name + ']' + ": " + msg).c_str(), msg.size() + name.size() + 4);   
                            }
                        }
                    }
                }
            }
        }
    }
    close(m_epld);
    close(m_sockfd);

    return 0;
}