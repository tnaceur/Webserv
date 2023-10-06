# include "request.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <strings.h>
#include <sys/_types/_off_t.h>
#include <sys/_types/_size_t.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <vector>

ofstream file("file", std::ios_base::trunc);
// std::ofstream f1("taha", std::ios::trunc);

void request::get_chunk_size()
{
    size_t f = stream->str().find("\r\n");
    if (f == std::string::npos)
        throw  stream->str().find("\r\n");
    std::string chunk = stream->str().substr(0, (f == 1) ? 1 : f - 1);
    char *end;
    chunkSize = strtol(chunk.c_str(), &end, 16);
    if (*end != '\0')
        throw 99;
    stream->str(stream->str().substr(stream->str().find("\r\n") + 2));
    if (chunkSize == 0)
    {
        ready = true;
        file.close();
        return ;
    }
}

void request::chunkedRequest()
{

    // if (chunkSize == 0)
    // {
        
    //     // std::string chunk = stream->str().substr(0, stream->str().find("\r\n"));
    //     // char *end;
    //     // chunkSize = strtol(chunk.c_str(), &end, 16);
    //     // stream->str(stream->str().substr(stream->str().find("\r\n") + 2));
    //     // // std::cout << "new length :: " << stream->str().length() << std::endl;
    //     // // cout << "chunkSize = " << chunkSize << std::endl;
    //     // if (chunkSize == 0)
    //     // {
    //     //     ready = true;
    //     //     return ;
    //     // }
    // }
    try {
        if (chunkSize == 0)
            get_chunk_size();
        if (chunkSize && chunkSize > stream->str().length())
        {
            std::cout << "<<" << chunkSize<< " > " << stream->str().length() << ">>"  << std::endl;
            return ;
        }
        if (chunkSize && chunkSize <= stream->str().length())
        {
            std::cout << "<<" << chunkSize<< " == " << stream->str().length() << ">>"  << std::endl;
            std::string chunk = stream->str().substr(0, chunkSize);
            if (int pos = chunk.find("\r\n") != std::string::npos)
                cout << "there is in  = " << pos << std::endl;
            file << chunk;
            if (stream->str().length() == chunkSize)
                stream->str("");
            else
                stream->str(stream->str().substr(chunkSize + 2));
            if (stream->str().empty())
                return ;
            chunkSize = 0;
        }
    }
    catch (size_t i)
    {
        // std::cout << "size is " << i << std::endl;
    }
    
}


void request::parseRequest(socket_t fd)
{
    // struct stat fileStat;

    char buffer[1024];
    if (counte == 0)
        stream = new stringstream;
    
    int f;
    bzero(buffer, 1024);
    f = recv(fd, buffer, 1024, 0);
    if (f < 0)
    {
        perror("read");
        return ;
    }
    counte++;
    // std::cout << counte << std::endl;
    // f1 << buffer;
    // if (f < 1024)
    //     f1.close();
    stream->write(buffer, f);
    // fstat(fd, &fileStat);
    if (counte == 1)
        request_string = buffer;
    if (request_string.find("Transfer-Encoding: chunked") != std::string::npos)
    {
        if (counte == 1 && request_string.find("\r\n\r\n") != std::string::npos)
            stream->str(stream->str().substr(stream->str().find("\r\n\r\n") + 4));
        chunkedRequest();
        return;
    }
    // if (counte == 1 && request_string.find("POST") == std::string::npos)
    // {
    //     ready = true;
    //     return ;
    // }
    // if (fileStat.st_size == 0) {
    //     // cout << counte << endl;
    //     counte = 0;
    //     ready = true;
    //     ofstream uu("hello", std::ios::trunc);
    //     uu << stream->str();
    // }
}
