#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <string>
#include "ip.h"

using namespace std;

class Client {
    public:
        Client(string _name, string _server_ip, string _router_ip, string _router_port);
        void set_ip(string _ip);
    private:
        string name;
        IP server_ip;
        IP router_ip;
        IP router_port;
        IP ip;
};

#endif