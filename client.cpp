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
    cout << "heloooooooooooooooo2" <<endl;
}

void Client::set_ip(string _ip)
{
    ip = IP(_ip);
}

string Client::readOnFd(int fd){
    char buffer[1024];
    memset(buffer, 0, 1024);
    read(fd, buffer, 1024);
    string result = buffer;
    cout << "client " << name << " : \"" << result << "\"" <<endl;
    return result;
}

void Client::listen(){
    string message;
    while (1)
    {
        fd_set readfds;
        int maxfd;
        int selectedFd;

        FD_ZERO(&readfds);
        FD_SET(commandFd, &readfds);
        FD_SET(inFd, &readfds);
        maxfd = (commandFd > inFd) ? commandFd : inFd;
        cout << "heloooooooooooooooo3" <<endl;

        select(maxfd + 1, &readfds, NULL, NULL, NULL);
        cout << "heloooooooooooooooo4" <<endl;

        if(FD_ISSET(commandFd, &readfds)){
            cout << "heloooooooooooooooo5" <<endl;
            message = readOnFd(commandFd);
            handleCmd(message);
        }

        // if(FD_ISSET(inFd, &readfds)){
        //     message = readOnFd(inFd);
        //     handleFrame(message);
        // }
    }
}

int Client::handleCmd(string command){
    commandArg.clear();
    commandArg = split(command, ' ');

    if (commandArg[0] == "exit"){
        cout << "in exit" <<endl;
        exit(EXIT_SUCCESS);
    }
    else if (commandArg[0] == "connectClient"){
        makeConnectionToRouter(commandArg[1], commandArg[2], commandArg[3]);
    }
    // else if (commandArg[0] == "send"){
    //     int dest = stoi(commandArg[2]);
    //     string fileName = commandArg[3];
    //     send(dest, fileName);
    // }
    // else if (commandArg[0] == "receive"){
    //     int dest = stoi(commandArg[2]);
    //     string fileName = commandArg[3];
    //     receive(dest, fileName);
    // }
    return 0;
}

void Client::makeConnectionToRouter(string routerName, string routerIp, string portNum){
    string fifoName;
    
    router_ip = IP(routerIp);
    router_port = stoi(portNum);

    fifoName = "./pipes/router_" + routerName + "_" + portNum + "_in";
    outFd = open(fifoName.c_str(), O_WRONLY);
    
    fifoName = "./pipes/router_" + routerName + "_" + portNum + "_out";
    inFd = open(fifoName.c_str(), O_RDONLY);

    cout << routerName << " " << routerIp << " " << portNum << "###########" <<endl;
}

void Client::run(){
    listen();
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    Client* client = new Client(argv[1], argv[2], argv[3], argv[4]);
    
    client->run();

    cout << argv[1] <<endl;
    cout << argv[2] <<endl;
    cout << argv[3] <<endl;
    cout << argv[4] <<endl;
}