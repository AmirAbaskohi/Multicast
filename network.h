#ifndef NETWORK
#define NETWORK

#include "utilities.h"

#define MAKE_CLIENT "client"
#define MAKE_ROUTER "router"
#define CONNECT_CLIENT_COMMAND "connectClient"
#define CONNECT_ROUTER_COMMAND "ConnectRouter"

#define SEND_COMMAND "Send"
#define RECEIVE_COMMAND "Receive"
#define SPANING_COMMAND "Span"

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
        
        int detectCommand();
        void killAllProcessses();

        
        void sendCommandSend();
        void sendCommandReceive();
        void sendMessageOnPipe(string fifoName, string message);
        void removeCycle();


        void sendNewClientConnectionMessage();
        void sendNewRouterConnectionMessage();
        void makeNewRouter();
        void makeNewClient();

        int find(vector<string> set, string value);
        
};

#endif