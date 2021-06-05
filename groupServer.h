#include <iostream>
#include <string>

using namespace std;

class GroupServer {
    public:
        GroupServer(string _name, string _server_ip);
    private:
        string name;
        string server_ip;
};