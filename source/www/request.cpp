# include "request.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
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


// std::ofstream f1("taha", std::ios::trunc);


long hexToDec(std::string hex)
{
    std::stringstream ss;
    ss << std::hex << hex;
    long decimal;
    ss >> decimal;
    if (ss.fail() || ss.bad())
        throw std::invalid_argument(hex /*"invalid hex number."*/);
    return decimal;
}

void request::get_chunk_size()
{
    size_t f = stream.str().find("\r\n");
    if (f == std::string::npos)
        throw  stream.str().find("\r\n");
    std::string chunk = stream.str().substr(0, (f == 1) ? 1 : f - 1);
    char *end;
    chunkSize = hexToDec(chunk);
    // chunkSize = strtol(chunk.c_str(), &end, 16);
    // if (*end != '\0')
    //     throw 99;
    f = stream.str().find("\r\n");
    if (f + 2 < stream.str().length())
        stream.str(stream.str().substr(stream.str().find("\r\n") + 2));
    else
        stream.str("");
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
        
    //     // std::string chunk = stream.str().substr(0, stream.str().find("\r\n"));
    //     // char *end;
    //     // chunkSize = strtol(chunk.c_str(), &end, 16);
    //     // stream.str(stream.str().substr(stream.str().find("\r\n") + 2));
    //     // // std::cout << "new length :: " << stream.str().length() << std::endl;
    //     // // cout << "chunkSize = " << chunkSize << std::endl;
    //     // if (chunkSize == 0)
    //     // {
    //     //     ready = true;
    //     //     return ;
    //     // }
    // }
    try {
        if (chunkSize < stream.str().length())
        {
            std::stringstream tmp;
            tmp.str(stream.str().substr(0, chunkSize));
            file << tmp.str();
            stream.str(stream.str().substr(chunkSize + 2));
            chunkSize = hexToDec(stream.str());
            if (chunkSize == 0)
                ready = true;
//                UpdateStatus(BODY_STATUS | BODY_DONE);
            stream.str(stream.str().substr(stream.str().find("\r\n") + 2));
        }
        if (chunkSize - stream.str().length() >= stream.str().length())
        {
            chunkSize -= stream.str().length();
//            s_write(bodycontent, stream);
            file << stream.str();
            stream.str("");
        }
//        if (chunkSize == 0)
//            get_chunk_size();
//        if (chunkSize && chunkSize > stream.str().length())
//        {
//            std::cout << "<<" << chunkSize<< " > " << stream.str().length() << ">>"  << std::endl;
//            return ;
//        }
//        if (chunkSize && chunkSize <= stream.str().length())
//        {
//            std::cout << "<<" << chunkSize<< " == " << stream.str().length() << ">>"  << std::endl;
//            std::string chunk = stream.str().substr(0, chunkSize);
//            if (int pos = chunk.find("\r\n") != std::string::npos)
//                cout << "there is in  = " << pos << std::endl;
//            file << chunk;
//            if (stream.str().length() > chunkSize + 2)
//                stream.str(stream.str().substr(chunkSize + 2));
//            else
//                stream.str("");
//            chunkSize = 0;
//            // if (stream.str().empty())
//            //     return ;
//        }
    }
    catch (size_t i)
    {
        std::cout << "exception " << i << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    
}


void request::parseRequest(socket_t fd)
{
    // struct stat fileStat;

    char buffer[1024];
    
    int f;
    bzero(buffer, 1024);
    f = read(fd, buffer, 1023);
    if (f < 0)
    {
        perror("read");
        return ;
    }
    buffer[f] = '\0';
    counte++;
    // std::ostream os()
    stream.write(buffer, f);
    // stream.write(buffer, f);
    if (counte == 1)
        request_string = buffer;
    if (request_string.find("Transfer-Encoding: chunked") != std::string::npos)
    {
        if (counte == 1 && request_string.find("\r\n\r\n") != std::string::npos)
        {
            stream.str(stream.str().substr(stream.str().find("\r\n\r\n") + 4));
            chunkSize = hexToDec(stream.str());
            stream.str(stream.str().substr(stream.str().find("\r\n") + 2));
        }
        chunkedRequest();
        return;
    }
    // if (counte == 1 && request_string.find("POST") == std::string::npos)§
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
