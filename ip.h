#ifndef _IP
#define _IP

#include <string>
#include <vector>
#include "utilities.h"

using namespace std;

class IP {
    public:
        IP(string _ip);
        IP();
        int compare(IP _ip);
        string get_first_part();
        string get_second_part();
        string get_third_part();
        string get_forth_part();
        string ip;

        bool operator <(const IP& ip2) const
        {
            return ip < ip2.ip;
        }
    private:
        string first_part;
        string second_part;
        string third_part;
        string forth_part;
        
};

#endif