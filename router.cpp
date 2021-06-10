#include "router.h"

Router::Router(string _name, string _ip, string _numOfPorts)
{
    cout << "h3" <<endl;
    name = _name;
    ip = IP(_ip);
    numOfPorts = stoi(_numOfPorts);

    enablePorts = vector<bool>(numOfPorts, false);
    isRouter = vector<bool>(numOfPorts, false);
    inFds = vector<int>(numOfPorts, 0);
    outFds = vector<int>(numOfPorts, 0);
    routingTable = vector<vector<string>>(5, vector<string>(2, ""));

    string fifoName = "./pipes/router_" + name + "_cmd";
    remove(fifoName.c_str());
    mkfifo(fifoName.c_str(), 0666);

    for(int i = 0; i < numOfPorts; i++){
        string fifoName = "./pipes/router_" + name + "_" + to_string(i) + "_in";
        remove(fifoName.c_str());
        mkfifo(fifoName.c_str(), 0666);
        fifoName = "./pipes/router_" + name + "_" + to_string(i) + "_out";
        remove(fifoName.c_str());
        mkfifo(fifoName.c_str(), 0666);
    }

    cout << "router " << name << " : created" <<endl;
    commandFd = open(fifoName.c_str(), O_RDONLY);
}

string Router::readOnFd(int fd){
    char buffer[1024];
    memset(buffer, 0, 1024);
    read(fd, buffer, 1024);
    string result = buffer;
    cout << "client " << name << " : \"" << result << "\"" <<endl;
    return result;
}

void Router::listen(){
    string message;
    while (1)
    {
        fd_set readfds;
        int maxfd;
        int selectedFd;

        FD_ZERO(&readfds);
        FD_SET(commandFd, &readfds);
        maxfd = commandFd;

        for ( int i = 0 ; i < inFds.size() ; i++)  
        {
            if (enablePorts[i] == false){
                continue;
            }
                
            int sd = inFds[i];
            if (sd > 0)
                FD_SET(sd, &readfds);
                    
            if (sd > maxfd)
                maxfd = sd;
        }

        select(maxfd + 1, &readfds, NULL, NULL, NULL);

        if(FD_ISSET(commandFd, &readfds)){
            message = readOnFd(commandFd);
            handleCmd(message);
        }

        // for ( int i = 0 ; i < inFds.size() ; i++)  
        // {
        //     if(FD_ISSET(inFds[i], &readfds)){
        //         message = readOnFd(inFds[i]);
        //         handleFrame(message, i);
        //     }
        // }
    }
}

int Router::handleCmd(string command){
    commandArg.clear();
    commandArg = split(command, ' ');

    if (commandArg[0] == "exit"){
        cout << "Process has exited" <<endl;
        exit(EXIT_SUCCESS);
    }
    else if (commandArg[0] == "connectClient"){
        makeNewClientConnection(commandArg[3], stoi(commandArg[4]));
    }
    // else if (commandArg[0] == "connectSwitch"){
    //     int portNum = stoi(commandArg[2]);
    //     int otherSwitchNum = stoi(commandArg[3]);
    //     int otherPort = stoi(commandArg[4]);
    //     makeConnectionSwitch(portNum, otherSwitchNum, otherPort);
    // }
    // else if (commandArg[0] == "span"){
    //     spaningTree(-1);
    // }
    return 0;
}

void Router::makeNewClientConnection(string client_ip, int port){
    string fifoName;

    enablePorts[port] = true;

    fifoName = "./pipes/router_" + name + "_" + to_string(port) + "in";
    inFds[port] = open(fifoName.c_str(), O_RDONLY);
    
    fifoName = "./pipes/router_" + name + "_" + to_string(port) + "out";
    outFds[port] = open(fifoName.c_str(), O_WRONLY);

    cout << "@@@@@@@@@@@@@"<<endl;

    //todo
}


void Router::run(){
    listen();
}

int main(int argc, char* argv[])
{
    cout << "h1" <<endl;
    if (argc != 4)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }
    Router* router = new Router(argv[1], argv[2], argv[3]);
    router->run();
    
}