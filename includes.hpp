#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>


struct Multiplexing{
    bool is_server;
    int sock_id;
};

struct WebServ{
    std::vector<Multiplexing> sockets;
};