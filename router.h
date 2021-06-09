#ifndef ROUTER
#define ROUTER

#include <iostream>
#include <string>
#include "ip.h"

using namespace std;

class Router {
    public:
        Router(string _name, string _ip, string _numOfPorts);
    private:
        int commandFd;

        string name;
        IP ip;
        int numOfPorts;
};

#endif