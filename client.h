#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <string>
#include "ip.h"

using namespace std;

class Client {
    public:
        Client(string _name, string _ip, string _router_ip, string _router_port);
        void set_ip(string _ip);
    private:
        int commandFd;

        string name;
        IP router_ip;
        int router_port;
        IP ip;
};

#endif