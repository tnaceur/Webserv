# ifndef _REQUEST_H_
# define _REQUEST_H_

# include "../core/config.hpp"
# include "socket.hpp"
# include "Header.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>

enum METHODS {
    GET,
    POST ,
    DELETE 
};

class request 
{
    public :
        request() {
            std::cout << "request constructor" << std::endl;
            counte = 0;
            chunkSize = 0;
            stream = new std::stringstream();
        };
        ~request() {
            std::cout << "request destructor" << std::endl;
            delete stream;
         };
        // copy constructor
        request(const request& other)
        {
            *this = other;
        }
        // copy assignment operator
        request& operator=(const request& other)
        {
            std::cout << "request copy constructor " << std::endl;
            if (this != &other) // self-assignment check expected
            {
                // do the copy
                this->stream = other.stream;
                this->request_string = other.request_string;
                this->httpMethod = other.httpMethod;
                this->path_ = other.path_;
                this->line_ = other.line_;
                this->query_ = other.query_;
                this->header_ = other.header_;
                this->ready = other.ready;
                this->counte = other.counte;
                this->chunkSize = other.chunkSize;
            }
            return *this;
        }
        void parseRequest(socket_t fd);
        bool isReady() { return ready; };
        void chunkedRequest();


    private :
        stringstream  *stream;
        std::string   request_string;
        METHODS       httpMethod;
        string        path_;
        string        line_;
        string        query_;
        Header        header_;
        bool          ready;
        int           counte;
        long           chunkSize;
        void get_chunk_size();
        // body
    
};

# endif