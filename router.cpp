#include "router.h"

Router::Router(string _name, string _ip, string _numOfPorts)
{
    name = _name;
    ip = IP(_ip);
    numOfPorts = stoi(_numOfPorts);

    enablePorts = vector<bool>(numOfPorts + 1, false);
    isRouter = vector<bool>(numOfPorts + 1, false);
    inFds = vector<int>(numOfPorts + 1, 0);
    outFds = vector<int>(numOfPorts + 1, 0);

    string fifoName = "./pipes/router_" + name + "_cmd";
    remove(fifoName.c_str());
    mkfifo(fifoName.c_str(), 0666);

    for(int i = 1; i < numOfPorts+1; i++){
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
    cout << "router " << name << " : \"" << result << "\"" <<endl;
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

        for (int i = 0 ; i < inFds.size() ; i++)  
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

        for ( int i = 0 ; i < inFds.size() ; i++)  
        {
            if(FD_ISSET(inFds[i], &readfds)){
                message = readOnFd(inFds[i]);
                handleFrame(message, i);
            }
        }
    }
}

void Router::handleFrame(string frame, int port){
    vector<string> frameSplit = split(frame, '#');
    string message;

    // if (frameSplit[0] == "lookFor"){
    //     if(frameSplit[1] == to_string(systemNumber)){
    //         message = "finded#" + to_string(systemNumber);
    //         write(outFd, message.c_str(), message.size());
    //     }
    //     return;
    // }

    if (frameSplit[0] == "dataframe"){
        IP src = IP(frameSplit[1]);
        IP dest = IP(frameSplit[2]);

        int destPort = findDestPort(dest);
        
        if(destPort == 0){
            cout << "Destination port not found" <<endl;
        }
        write(outFds[destPort], frame.c_str(), frame.size() + 1);
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
    else if (commandArg[0] == "connectRouter"){
        makeNewRouterConnection();
    }
    return 0;
}

void Router::makeNewClientConnection(string client_ip, int port){
    string fifoName;

    enablePorts[port] = true;

    fifoName = "./pipes/router_" + name + "_" + to_string(port) + "_in";
    inFds[port] = open(fifoName.c_str(), O_RDONLY);
    
    fifoName = "./pipes/router_" + name + "_" + to_string(port) + "_out";
    outFds[port] = open(fifoName.c_str(), O_WRONLY);

    routingTable[IP(client_ip)] = port;
}

void Router::makeNewRouterConnection(){

    string name1 = commandArg[1], name2 = commandArg[3];
    string ip1 = commandArg[2], ip2 = commandArg[4];
    int port1 = stoi(commandArg[5]), port2 = stoi(commandArg[6]);

    string fifoName1, fifoName2;
    fifoName1 = "./pipes/router_" + name1 + "_" + to_string(port1) + "_in";
    fifoName2 = "./pipes/router_" + name2 + "_" + to_string(port2) + "_in";

    enablePorts[port1] = true;
    isRouter[port1] = true;

    if (name1 > name2){
        inFds[port1] = open(fifoName1.c_str(), O_RDONLY);
        outFds[port1] = open(fifoName2.c_str(), O_WRONLY);
    }
    else{
        outFds[port1] = open(fifoName2.c_str(), O_WRONLY);
        inFds[port1] = open(fifoName1.c_str(), O_RDONLY);
    }

    routingTable[IP(ip2)] = port1;

}

int Router::findDestPort(IP ip){
    map<IP, int>::iterator it = routingTable.begin();
    int maxMatchedPrefix = 0;
    IP max, temp;

    while (it != routingTable.end())
    {
        temp = it->first;

        if (ip.compare(temp) > maxMatchedPrefix){
            maxMatchedPrefix = ip.compare(temp);
            max = it->first;
        }
        it++;
    }
    return routingTable[max];
}

void Router::run(){
    listen();
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }
    Router* router = new Router(argv[1], argv[2], argv[3]);
    router->run();
    
}