#include "network.h"
Network::Network(){
    mkdir("dirs", 0777);
}

void Network::makeNewClient(){
    string name = commandArguments[1];
    
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
    string name = commandArguments[1];

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



// void Network::sendNewConnectionMessage(){
//     int systemNum = stoi(commandArguments[1]);
//     int switchNum = stoi(commandArguments[2]);
//     int portNum = stoi(commandArguments[3]);
//     if (find(systemNumbers, systemNum) < 0){
//         cout << "Error : System Does not exist!" <<endl;
//         return;
//     }
//     if (find(switchNumbers, switchNum) < 0){
//         cout << "Error : Switch Does not exist!" <<endl;
//         return;
//     }
//     string fifoNameSwitch = "./pipes/switch" + to_string(switchNum) + "cmd";
//     string fifoNameSystem = "./pipes/system" + to_string(systemNum) + "cmd";
//     string message = "connect " + to_string(switchNum) + " " + to_string(portNum - 1) + "\0";
//     sendMessageOnPipe(fifoNameSwitch, message);
//     sendMessageOnPipe(fifoNameSystem, message);
// }

// void Network::sendNewSwitchConnectionMessage(){
//     int switchNum1 = stoi(commandArguments[1]);
//     int portNum1 = stoi(commandArguments[2]);
//     int switchNum2 = stoi(commandArguments[3]);
//     int portNum2 = stoi(commandArguments[4]);
//     if (find(switchNumbers, switchNum1) < 0 || find(switchNumbers, switchNum2) < 0){
//         cout << "Error : Switch Does not exist!" << endl;
//         return;
//     }
//     string fifoNameSwitch1 = "./pipes/switch" + to_string(switchNum1) + "cmd";
//     string fifoNameSwitch2 = "./pipes/switch" + to_string(switchNum2) + "cmd";
//     string message1 = "connectSwitch " + to_string(switchNum1) + " " + to_string(portNum1 - 1) 
//                     + " " + to_string(switchNum2) + " " + to_string(portNum2 - 1) + "\0";
//     string message2 = "connectSwitch " + to_string(switchNum2) + " " + to_string(portNum2 - 1) 
//                     + " " + to_string(switchNum1) + " " + to_string(portNum1 - 1) + "\0";
//     sendMessageOnPipe(fifoNameSwitch1, message1);
//     sendMessageOnPipe(fifoNameSwitch2, message2);
// }

// void Network::sendCommandSend(){
//     int systemNum1 = stoi(commandArguments[1]);
//     int systemNum2 = stoi(commandArguments[2]);
//     if (find(systemNumbers, systemNum1) < 0 || find(systemNumbers, systemNum2) < 0){
//         cout << "Error : System Does not exist!" << endl;
//         return;
//     }
//     string fifoNameSystem = "./pipes/system" + to_string(systemNum1) + "cmd";
//     string message = "send " + to_string(systemNum1) + " " + to_string(systemNum2) + " " + commandArguments[3] + "\0";
//     sendMessageOnPipe(fifoNameSystem, message);
// }

// void Network::sendCommandReceive(){
//     int systemNum1 = stoi(commandArguments[1]);
//     int systemNum2 = stoi(commandArguments[2]);
//     if (find(systemNumbers, systemNum1) < 0 || find(systemNumbers, systemNum2) < 0){
//         cout << "Error : System Does not exist!" << endl;
//         return;
//     }
//     string fifoNameSystem = "./pipes/system" + to_string(systemNum1) + "cmd";
//     string message = "receive " + to_string(systemNum1) + " " + to_string(systemNum2) + " " + commandArguments[3] + "\0";
//     sendMessageOnPipe(fifoNameSystem, message);
// }

// void Network::removeCycle(){
//     int switchNum = stoi(commandArguments[1]);
//     string fifoNameSwitch = "./pipes/switch" + to_string(switchNum) + "cmd";
//     string message = "span";
//     sendMessageOnPipe(fifoNameSwitch, message);
// }

// void Network::sendMessageOnPipe(string fifoName, string message){
//     int fd = open(fifoName.c_str(), O_WRONLY);
//     write(fd, message.c_str(), message.size() + 1);
// }

int Network::detectCommand()
{
    if (commandArguments.size() == 0)
        return -1;

    if (commandArguments[0] == string(MAKE_CLIENT) && commandArguments.size() == 5){
        makeNewClient();
    }
    else if (commandArguments[0] == string(MAKE_ROUTER) && commandArguments.size() == 4){
        cout << "***********" <<endl;
        makeNewRouter();
    }
    // else if (commandArguments[0] == string(CONNECT_COMMAND) && commandArguments.size() == 4){
    //     sendNewConnectionMessage();
    // }
    // else if (commandArguments[0] == string(CONNECT_SWITCH_COMMAND) && commandArguments.size() == 5){
    //     sendNewSwitchConnectionMessage();
    // }
    // else if (commandArguments[0] == string(SEND_COMMAND) && commandArguments.size() == 4){
    //     sendCommandSend();
    // }
    // else if (commandArguments[0] == string(RECEIVE_COMMAND) && commandArguments.size() == 4){
    //     sendCommandReceive();
    // }
    // else if (commandArguments[0] == string(SPANING_COMMAND) && commandArguments.size() == 2){
    //     removeCycle();
    // }
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
        cout << requests[i] <<endl;
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

    // killAllProcessses();
}

int Network::find(vector<string> set, string value){
    for (int i = 0; i < set.size(); i++){
        if (set[i] == value)
            return i;
    }
    return -1;
}

// void Network::killAllProcessses(){
//     for(int i = 0; i < switchNumbers.size(); i++){
//         string fifoName = "./pipes/switch" + to_string(switchNumbers[i]) + "cmd"; 
//         int fd = open(fifoName.c_str(), O_WRONLY);
//         write(fd, "exit\0", strlen("exit\0"));
//     }
//     for(int i = 0; i < systemNumbers.size(); i++){
//         string fifoName = "./pipes/system" + to_string(switchNumbers[i]) + "cmd"; 
//         int fd = open(fifoName.c_str(), O_WRONLY);
//         write(fd, "exit\0", strlen("exit\0"));
//     }
// }

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