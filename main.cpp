#include "includes.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

const char * response = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Content-Length: 12\r\n"
                        "\r\n"
                        "Hello, World!";

int  main1(int ac, char **av)
{
    WebServ webserv;
    int web_socket;
    int error;
    struct addrinfo *addr;
    struct addrinfo hint;
    hint.ai_family = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;
    for (int i = 0; i < 1; i++)
    {
        if (getaddrinfo("127.0.0.1", "8080", &hint, &addr) < 0)
            return (void)(std::cerr << "Invalid address.\n"), 1;
        for (struct addrinfo *tmp = addr; tmp; tmp = tmp->ai_next)
        {
            web_socket = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
            error = bind(web_socket, tmp->ai_addr, tmp->ai_addrlen);
            if (error != -1)
                break ;
            close(web_socket);
        }
        if (error == -1)
            return ((void)(perror(NULL)), (void)close(web_socket), freeaddrinfo(addr), 1);
        listen(web_socket, 10);
        webserv.sockets.push_back((Multiplexing){.is_server = true, .sock_id = web_socket});
    }
    while (1)
    {
        
        webserv.sockets.push_back((Multiplexing){.is_server = false, .sock_id = accept(webserv.sockets[0].sock_id, NULL, NULL)}); 
        if (webserv.sockets.back().sock_id < 0)
        {
            std::cerr << "Failed to accept connection." << std::endl;
            return 1;
        }
        else
           send(webserv.sockets.back().sock_id, response, strlen(response), 0);
        close(webserv.sockets.back().sock_id);
        webserv.sockets.pop_back();
    }
    close(web_socket);
    return 0;
}

int main(int ac, char **av)
{
    main1(ac, av);
    system("leaks Webserv");
}