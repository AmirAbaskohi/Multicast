#include "router.h"

Router::Router(string _name, string _ip, string _numOfPorts)
{
    name = _name;
    ip = IP(_ip);
    numOfPorts = stoi(_numOfPorts);

    string fifoName = "./pipes/router_" + name + "_cmd";
    remove(fifoName.c_str());
    mkfifo(fifoName.c_str(), 0666);

    cout << "router " << name << " : created" <<endl;
    commandFd = open(fifoName.c_str(), O_RDONLY);
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    Router* router = new Router(argv[1], argv[2], argv[3]);
    cout << argv[1] <<endl;
    cout << argv[2] <<endl;
    cout << argv[3] <<endl;
}