#include "client.h"

Client::Client(string _name, string _ip, string _router_ip, string _router_port)
{
    name = _name;
    router_ip = IP(_router_ip);
    router_port = stoi(_router_port);
    ip = IP(_ip);

    string fifoName = "./pipes/client_" + name + "_cmd";
    remove(fifoName.c_str());
    mkfifo(fifoName.c_str(), 0666);

    cout << "client " << name << " : created" <<endl;
    commandFd = open(fifoName.c_str(), O_RDONLY);
}

void Client::set_ip(string _ip)
{
    ip = IP(_ip);
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    Client* client = new Client(argv[1], argv[2], argv[3], argv[4]);

    cout << argv[1] <<endl;
    cout << argv[2] <<endl;
    cout << argv[3] <<endl;
    cout << argv[4] <<endl;
}