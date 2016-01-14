#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <unistd.h>
#include <math.h>

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

	int counter = 0;

	while (getline(infile, line))
	{
		last = curr;
		curr = stol(split(line, ' ')[5]);
		diff = curr - last; //difference between current and last value (1s ago)
		load = 1 - ((float)diff / 100) / (float)coreCount; //calc load as 0...1 float
		cout << diff << "\t" << load << "\t" ;
	
		//turn LEDs on:
		for(int i = 0; i < 10; i++){
			if (i + 1 <= round(load * 10)) {
				cout << "1";
	 		} else {
				cout << "0";
			}
		}
		cout << endl;
		
		//go back to begin of file:
		infile.clear();
		infile.seekg(0, ios::beg);

		counter ++;

		//sleep for 1s
		sleep(1);

		if (counter >= 10) { // 10 secounds after start
			infile.close();
			break;	
		}
	}

	return 0;
}
