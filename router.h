#ifndef ROUTER
#define ROUTER

#include <iostream>
#include <string>

using namespace std;

class Router {
    public:
        Router(string _listen_port);
    private:
        string listen_port;
};

#endif