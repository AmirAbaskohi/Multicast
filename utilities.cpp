#include "utilities.h"

vector<string> split(string str, char divider)
{
    stringstream ss(str);
    string word;
    vector< string> result;

    while(getline(ss, word, divider))
    {
        if(word != "")
            result.push_back(word);
    }
    return result;
}

vector<string> SplitToPackets(string data, int packet_size)
{
    vector<string> packets;
    for(int i=0; i < data.size(); i += packet_size){
        packets.push_back(data.substr(i, packet_size));
    }
    return packets;
}

string readFile(string fileName){
    ifstream file;
    string line, data;
    file.open(fileName, ios::in);
    if(!file){
        cout << "** cannot open file **" <<endl;
    }
    while(getline(file, line)){
        data += line + "\n";
    }
    return data;
}