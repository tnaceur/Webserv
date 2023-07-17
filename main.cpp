#include "includes.hpp"
#include <cstdio>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>

int  main(int ac, char **av)
{
    /* socket() creat new socket and return the socket descriptor */
    int web_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (web_socket < 0)
        return (void)(std::cerr << "socket error: \n"), 1;
    /* sockaddr_in is a sturct that contain information about the server it's 'ip, port' ... */
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    if (inet_pton(AF_INET, "10.11.2.9", &(addr.sin_addr)) < 0)
        return (void)(std::cerr << "Invalid address.\n"), 1;
    addr.sin_port = htons(5555);
    if (bind(web_socket, (struct sockaddr*)(&addr), sizeof(addr)) < 0)
        return (void)(perror(NULL)), 1;
    listen(web_socket, 10);
    int client = accept(web_socket, NULL, NULL);
    send(client, "Hello world\n", 12, 0);
    close(web_socket);
    close(client);
    return 0;
    
}
