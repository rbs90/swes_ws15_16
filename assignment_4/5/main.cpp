#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <math.h>
#include <time.h>

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

long getTimeDifference(chrono::steady_clock::time_point start, chrono::steady_clock::time_point end){
	long difference = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	return difference;
}

long getTimeDifferenceToNow(chrono::steady_clock::time_point start){
	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	long difference = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	return difference;
}

int main(){
	unsigned coreCount = thread::hardware_concurrency();
	cout << coreCount << " CPU Cores detected..." << endl;
	
	ifstream infile("/proc/stat");
	string line;
	long curr, last, diff;
	float load;

	bool fastMode = true;
	long curr_time = 0;
	chrono::steady_clock::time_point time_start, time_last; //begin time, last time displayed
  	time_start = chrono::steady_clock::now();

	while (getTimeDifferenceToNow(time_start) <= 10000) {
		curr_time = getTimeDifferenceToNow(time_last);

		if(fastMode || curr_time > 1000) {
			time_last = chrono::steady_clock::now();
			getline(infile, line);
			last = curr;
			curr = stol(split(line, ' ')[5]);
			diff = curr - last; //difference between current and last value (1s ago)
			if (fastMode)
				load = 1 - ((float)diff / 100) * 50 / (float)coreCount; //calc load as 0...1 float			
			else
				load = 1 - ((float)diff / 100) / (float)coreCount; //calc load as 0...1 float

			cout << curr_time << "\t" << diff << "\t" << load << "\t" ;

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
		}

		//sleep for 20ms
		this_thread::sleep_for(chrono::milliseconds(20));

	}
	
	infile.close();
	return 0;
}
