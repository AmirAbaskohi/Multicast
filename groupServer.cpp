#include "groupServer.h"

GroupServer::GroupServer(string _name, string _server_ip)
{
    server_ip = _server_ip;
    name = _name;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    GroupServer* groupServer = new GroupServer(argv[1], argv[2]);
}