#include "ip.h"

IP::IP(string ip)
{
    vector<string> splitted_ip = split(ip, '.');
    first_part = splitted_ip[0];
    second_part = splitted_ip[1];
    third_part = splitted_ip[2];
    forth_part = splitted_ip[3];
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

int IP::compare(IP ip)
{
    string first_ip[4] = { first_part, second_part, third_part, forth_part };
    string second_ip[4] = { ip.get_first_part(), ip.get_second_part(), ip.get_third_part(), ip.get_forth_part() };

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