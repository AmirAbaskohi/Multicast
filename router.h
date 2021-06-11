#ifndef ROUTER
#define ROUTER

#include <iostream>
#include <string>
#include "ip.h"

using namespace std;

#define TABLE_SIZE 1024

class Router {
    public:
        Router(string _name, string _ip, string _numOfPorts);
        void run();
    private:
        int commandFd;
        vector<int> inFds, outFds;
        vector<bool> enablePorts;
        vector<bool> isRouter;
        vector<string> commandArg;

        // vector<vector<string>> routingTable;

        map<IP, int> routingTable;
        map<IP, vector<int>> multicastTable;

        string name;
        IP ip;
        int numOfPorts;

        string readOnFd(int fd);
        void listen();
        void handleFrame(string frame, int port);
        int handleCmd(string command);

        void makeNewClientConnection(string client_ip, int port);
        void makeNewRouterConnection();

        int findDestPort(IP ip);
        void addToMulticastTable(IP groupIp, int port);
        void removeFromMulticastTable(IP groupIp, int port);

        void sendBroadcast(string frame, int exceptPort, bool sendOnRouters);
        void sendMultiCast(string frame, int exceptPort);
        void sendUniCast(IP dest, string frame);

        void showTables();

};

#endif