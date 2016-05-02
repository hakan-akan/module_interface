#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

bool query_module(const std::string &m)
{
	fstream f("/proc/modules");
	
	string line;
	while (getline(f, line)) {
		stringstream ssf(line);
		unsigned long size, refs;
		string name;
		
		ssf >> name >> size >> refs;
		
		cout << "name " << name << endl; 
	}
}

bool remove_module(const std::string &m)
{
	
}

bool add_module(const std::string &m)
{
	
}