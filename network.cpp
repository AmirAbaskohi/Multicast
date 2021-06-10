#include "network.h"
Network::Network(){
    mkdir("dirs", 0777);
}

void Network::makeNewClient(){
    string name = commandArguments[1];
    clientIps[name] = commandArguments[2];
    
    if (find(clientNames, name) >= 0){
        cout << "Error : Duplicated Client Name!" <<endl;
        return;
    }
    clientNames.push_back(name);

    if (fork() == 0)
    {
        char *args[] ={ (char*)CLIENT_RUNNABLE, (char*)commandArguments[1].c_str(), (char*)commandArguments[2].c_str(),
                        (char*)commandArguments[3].c_str(), (char*)commandArguments[4].c_str(), NULL};
        execvp(args[0], args);
    }
}

void Network::makeNewRouter(){
    cout << "h2" <<endl;
    string name = commandArguments[1];
    routerIps[name] = commandArguments[2];

    if (find(routerNames, name) >= 0){
        cout << "Error : Duplicated Router Name!" <<endl;
        return;
    }
    routerNames.push_back(name);

    if (fork() == 0)
    {
        char *args[] ={ (char*)ROUTER_RUNNABLE, (char*)commandArguments[1].c_str(),
                        (char*)commandArguments[2].c_str(), (char*)commandArguments[3].c_str(), NULL};
        execvp(args[0], args);
    }
}

void Network::sendNewClientConnectionMessage(){
    string clientName = commandArguments[1];
    string routerName = commandArguments[2];
    string portNum = commandArguments[3];

    if (find(clientNames, clientName) < 0){
        cout << "Error : Client Does not exist!" <<endl;
        return;
    }
    if (find(routerNames, routerName) < 0){
        cout << "Error : Router Does not exist!" <<endl;
        return;
    }
    string fifoNameClient = "./pipes/client_" + clientName + "_cmd";
    string fifoNameRouter = "./pipes/router_" + routerName + "_cmd";
    string message = "connectClient " + routerName + " " +routerIps[routerName] + " " + clientIps[clientName] + " " + portNum + "\0";
    sendMessageOnPipe(fifoNameClient, message);
    sendMessageOnPipe(fifoNameRouter, message);
}

void Network::sendNewRouterConnectionMessage(){
    string routerName1 = commandArguments[1];
    string portNum1 = commandArguments[2];
    string routerName2 = commandArguments[3];
    string portNum2 = commandArguments[4];
    
    if (find(routerNames, routerName1) < 0 || find(routerNames, routerName2) < 0){
        cout << "Error : Router Does not exist!" << endl;
        return;
    }
    string fifoNameRouter1 = "./pipes/router_" + routerName1 + "_cmd";
    string fifoNameRouter2 = "./pipes/router_" + routerName2 + "_cmd";
    string message = "connectSwitch " + routerIps[routerName1] + " " + routerIps[routerName2] 
                    + " " + portNum1 + " " + portNum2 + "\0";

    sendMessageOnPipe(fifoNameRouter1, message);
    sendMessageOnPipe(fifoNameRouter2, message);
}

void Network::sendMessageOnPipe(string fifoName, string message){
    int fd = open(fifoName.c_str(), O_WRONLY);
    write(fd, message.c_str(), message.size() + 1);
}

int Network::detectCommand()
{
    if (commandArguments.size() == 0)
        return -1;

    if (commandArguments[0] == string(MAKE_CLIENT) && commandArguments.size() == 5){
        makeNewClient();
    }
    else if (commandArguments[0] == string(MAKE_ROUTER) && commandArguments.size() == 4){
        makeNewRouter();
    }
    else if (commandArguments[0] == string(CONNECT_CLIENT_COMMAND) && commandArguments.size() == 4){
        sendNewClientConnectionMessage();
    }
    else if (commandArguments[0] == string(CONNECT_ROUTER_COMMAND) && commandArguments.size() == 5){
        sendNewRouterConnectionMessage();
    }
    else return -1;
    return 0;    
}

void Network::run(string testFileName)
{
    string request;
    vector<string> requests;

    ifstream input("./tests/" + testFileName);

    while (getline(input, request))
    {
        if (request == "") continue;
        requests.push_back(request);
    }

    input.close();

    for (int i = 0; i < requests.size(); i++){
        commandArguments.clear(); 
        commandArguments = split(requests[i], ' ');
        sleep(1);

        if (detectCommand() == -1){
            cout << "Invalid command" << endl;
        }
    }

    while(getline(cin, request))
    {
        commandArguments.clear();
        commandArguments = split(request, ' ');

        if (detectCommand() == -1){
            cout << "Invalid command" << endl;
        }
    }

    killAllProcessses();
}

int Network::find(vector<string> set, string value){
    for (int i = 0; i < set.size(); i++){
        if (set[i] == value)
            return i;
    }
    return -1;
}

void Network::killAllProcessses(){
    for(int i = 0; i < clientNames.size(); i++){
        string fifoName = "./pipes/client_" + clientNames[i] + "_cmd"; 
        int fd = open(fifoName.c_str(), O_WRONLY);
        write(fd, "exit\0", strlen("exit\0"));
    }
    for(int i = 0; i < routerNames.size(); i++){
        string fifoName = "./pipes/router_" + routerNames[i] + "_cmd"; 
        int fd = open(fifoName.c_str(), O_WRONLY);
        write(fd, "exit\0", strlen("exit\0"));
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        cout << "Invalid arguments" << endl;
        exit(EXIT_FAILURE);
    }
    Network* network = new Network();

    network->run(argv[1]);

    exit(EXIT_SUCCESS);
}