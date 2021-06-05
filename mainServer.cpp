#include "mainServer.h"

MainServer::MainServer(string _server_ip)
{
    server_ip = _server_ip;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    MainServer* mainServer = new MainServer(argv[1]);
}