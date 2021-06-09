#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#ifndef UTILITIES
#define UTILITIES

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <map>
#include <thread>
#include <fstream>

#define SIZE_OF_DATA_IN_FRAME 1012

using namespace std;

vector<string> split(string str, char divider);

vector<string> SplitToPackets(string data, int packet_size);

string readFile(string fileName);

#endif