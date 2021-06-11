#ifndef CLIENT
#define CLIENT

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "ip.h"

using namespace std;

class Client {
    public:
        Client(string _name, string _ip);
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
        void writeOnFd(string message);
        void listen();
        void handleFrame(string frame);
        int handleCmd(string command);
        void makeConnectionToRouter(string routerName, string routerIp, string portNum);
        void sendData(string destIp, string message);
        void sendCreateGroup(string groupId);
        void sendJoinGroup(string senderIp, string groupIp);
        void sendLeaveGroup(string senderIp, string groupIp);
};

#endif