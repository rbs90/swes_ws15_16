#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <unistd.h>

using namespace std;

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

int main(){
	unsigned coreCount = thread::hardware_concurrency();
	cout << coreCount << " CPU Cores detected..." << endl;
	
	ifstream infile("/proc/stat");
	string line;
	long curr, last, diff;
	float load;

	while (getline(infile, line))
	{
		last = curr;
		curr = stol(split(line, ' ')[5]);
		diff = curr - last;
		load = 1 - ((float)diff / 100) / (float)coreCount;
		cout << diff << ": " << load << endl;
		

		//go back to begin of file:
		infile.clear();
		infile.seekg(0, ios::beg);

		//sleep for 1s
		sleep(1);
	}

	return 0;
}
