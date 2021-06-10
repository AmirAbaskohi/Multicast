#include "ip.h"

IP::IP(string _ip)
{
    vector<string> splitted_ip = split(_ip, '.');
    first_part = splitted_ip[0];
    second_part = splitted_ip[1];
    third_part = splitted_ip[2];
    forth_part = splitted_ip[3];

    ip = _ip;
}

IP::IP()
{
    first_part = second_part = third_part = forth_part = "0";
}

string IP::get_first_part()
{
    return first_part;
}

string IP::get_second_part()
{
    return second_part;
}

string IP::get_third_part()
{
    return third_part;
}

string IP::get_forth_part()
{
    return forth_part;
}

int IP::compare(IP _ip)
{
    string first_ip[4] = { first_part, second_part, third_part, forth_part };
    string second_ip[4] = { _ip.get_first_part(), _ip.get_second_part(), _ip.get_third_part(), _ip.get_forth_part()};

    int result = 0;

    for (int i = 0 ; i < 4 ; i++)
    {
        if (first_ip[i] == second_ip[i])
            result++;
        else
            break;
    }

    return result;
}