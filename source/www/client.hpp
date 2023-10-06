# ifndef _CLIENT_H_
# define _CLIENT_H_

# include "../core/config.hpp"
# include "socket.hpp"
# include "request.hpp"
# include "response.hpp"
#include <vector>

class response ; // waitng for creat
class request  ; // waiting for creat

class s_client
{
    private :
        response res_;
        request  req_;
    
        pid_t     _pid; // for cgi
        int       _fds[2]; // for cgi
        socket_t _newconnection; // new client
        socket_t _server_socket; // server socket
        int       _server_idx; // server index


    public :
        // copy constructor
        s_client(const s_client& other)
        {
            *this = other;
        }
        // copy assignment operator
        s_client& operator=(const s_client& other)
        {
            std::cout << "client copy constructor " << std::endl;
            if (this != &other) // self-assignment check expected
            {
                // do the copy
                this->_pid = other._pid;
                this->_fds[0] = other._fds[0];
                this->_fds[1] = other._fds[1];
                this->_newconnection = other._newconnection;
                this->_server_socket = other._server_socket;
                this->_server_idx = other._server_idx;
                this->req_ = other.req_;
                this->res_ = other.res_;
            }
            return *this;
        }
        s_client() {
            std::cout << "Client Constructor" << std::endl;
        };
        ~s_client() { 
            std::cout << "Client Destructor" << std::endl;
        };

        s_client(socket_t newconnection);
        
        void set_server_idx(int idx, int server_socket);

        socket_t get_client_socket();

        void DealwithRequest(  void );
        void DealwithResponce( void );
        bool isReady() { return req_.isReady();};
        void Expireconnection() {
            // std::cout << "they got here" << std::endl;
            // exit(EXIT_FAILURE); // hhhhhhh debug about 20 min fuck
            // waiting to remove iterator and close the fd
        }
};

// class Clients : public map<socket_t , s_client>
// {
//     public :
//         Clients() {}

// };

// extern Clients clients;
extern std::vector<s_client> clients;

# endif