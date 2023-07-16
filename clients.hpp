#ifndef CLIENTS_HPP
#define CLIENTS_HPP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class client
{
    int a = socket(AF_INET, SOCK_STREAM, 0);

};

#endif