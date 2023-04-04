#include"../include/header.h"
#include"../include/server.h"

int main(int argc, char** argv){
    
    Server server;
    std::cout << "server init successfully" << std::endl;
    server.init_epoll();
    std::cout << "epoll init successfully" << std::endl;
    server.start_epoll();    

    std::cin.get();
    return 0;
}
