#include "router.h"

Router::Router(string _listen_port)
{
    listen_port = _listen_port;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Error: Invalid arg number" << endl;
        exit(EXIT_FAILURE);
    }

    Router* router = new Router(argv[1]);
}