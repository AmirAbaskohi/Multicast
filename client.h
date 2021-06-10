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
        void run();
    private:
        vector<string> commandArg;
        int commandFd;
        int outFd, inFd;

        string name;
        IP router_ip;
        int router_port;
        IP ip;

        string readOnFd(int fd);
        void listen();
        int handleCmd(string command);
        void makeConnectionToRouter(string routerName, string routerIp, string portNum);
        
};

#endif