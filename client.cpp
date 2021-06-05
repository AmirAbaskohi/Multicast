#include "client.h"

Client::Client(string _name, string _server_ip, string _router_ip, string _router_port)
{
    name = _name;
    server_ip = _server_ip;
    router_ip = _router_ip;
    router_port = _router_port;
}

void Client::set_ip(string _ip)
{
    ip = _ip;
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    Client* client = new Client(argv[1], argv[2], argv[3], argv[4]);
}