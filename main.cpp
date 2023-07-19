#include "includes.hpp"
#include <cstdio>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

int  main(int ac, char **av)
{
    int web_socket = socket(AF_INET, SOCK_STREAM, 0);
    /* socket() creat new socket and return the socket descriptor */
    if (web_socket < 0)
        return (void)(std::cerr << "socket error: \n"), 1;
    /* sockaddr_in is a sturct that contain information about the server it's 'ip, port' ... */
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr)) < 0)
        return (void)(std::cerr << "Invalid address.\n"), 1;
    addr.sin_port = htons(8888);
    if (bind(web_socket, (struct sockaddr*)(&addr), sizeof(addr)) < 0)
        return (void)(perror(NULL)), 1;
    listen(web_socket, 10);
    int client;
    sockaddr_in clientAddr;
    socklen_t client_lenght = sizeof(clientAddr);
    while (1)
    {
       client = accept(web_socket, (struct sockaddr*)(&addr), &client_lenght);
       const char * response = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Content-Length: 12\r\n"
                          "\r\n"
                          "Hello, World!";
        if (client < 0) {
            std::cerr << "Failed to accept connection." << std::endl;
            return 1;
        }
        else
           send(client, response, strlen(response), 0);
    }
    close(client);
    close(web_socket);
    return 0;
    
}

