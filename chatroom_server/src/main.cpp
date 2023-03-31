#include"../include/header.h"
#include"../include/server.h"

int main(int argc, char** argv){
    
    Server server;
    server.init_epoll();
    server.start_epoll();    

    std::cin.get();
    return 0;
}