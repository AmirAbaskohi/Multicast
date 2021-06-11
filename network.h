#ifndef NETWORK
#define NETWORK

#include "utilities.h"
#include "ip.h"

#define MAKE_CLIENT "client"
#define MAKE_ROUTER "router"
#define CONNECT_CLIENT_COMMAND "connectClient"
#define CONNECT_ROUTER_COMMAND "connectRouter"
#define UNICAST_COMMAND "unicast"
#define MULTICAST_COMMAND "multicast"
#define CREATE_GROUP_COMMAND "createGroup"
#define JOIN_GROUP_COMMAND "joinGroup"
#define LEAVE_GROUP_COMMAND "leaveGroup"
#define GET_GROUPS_COMMAND "getGroups"
#define SHOW_TABLE_COMMAND "showTable"

#define CLIENT_RUNNABLE "./client.out"
#define ROUTER_RUNNABLE "./router.out"


using namespace std;

class Network
{
    public:
        Network();
        void run(string testFileName);
    private:

        vector<string> clientNames, routerNames;
        map<string, string>clientIps, routerIps;
        vector<string> commandArguments;
        map<string, string> senders;
        vector<string> groupsIp;
        
        int detectCommand();
        void killAllProcessses();

        void sendMakeGroup();
        void sendJoinGroup();
        void sendLeaveGroup();
        void sendGroupsIp();
        void sendShowTable();
        void sendMessageOnPipe(string fifoName, string message);
        void sendCommandUniCast();
        void sendCommandMultiCast();
        void sendNewClientConnectionMessage();
        void sendNewRouterConnectionMessage();
        void makeNewRouter();
        void makeNewClient();

        int find(vector<string> set, string value);
        
};

#endif