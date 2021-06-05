#include <iostream>
#include <string>

using namespace std;

class Client {
    public:
        Client(string _name, string _server_ip, string _router_ip, string _router_port);
        void set_ip(string _ip);
    private:
        string name;
        string server_ip;
        string router_ip;
        string router_port;
        string ip;
};