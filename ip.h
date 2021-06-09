#include <string>
#include <vector>
#include "utilities.h"

using namespace std;

class IP {
    public:
        IP(string ip);
        int compare(IP ip);
        string get_first_part();
        string get_second_part();
        string get_third_part();
        string get_forth_part();
    private:
        string first_part;
        string second_part;
        string third_part;
        string forth_part;
};