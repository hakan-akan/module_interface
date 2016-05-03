#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h> // getuid
#include <stdexcept>
#include <stdlib.h>

using namespace std;

bool verify_root()
{
	if (getuid()) {
		cout << "You must be root to do this!\n";
		return false;
	}
	return true; 	
}

bool query_module(const string &m)
{
	if (!verify_root()) return false;
	fstream f("/proc/modules");
	if (!f.is_open()) {
		cout << "failed opening /proc/modules\n";
		return false;
	}	
	string line;
	string name;
	size_t size, refs;
	while (getline(f, line)) {
		stringstream ssf(line);
		// Parse a line
		ssf >> name >> size >> refs;
		// match !!!
		if(m == name) return true;
	}
	return false;
}

bool remove_module(const string &m)
{
	if (!verify_root()) return false;
	string cmd = "/sbin/rmmod " + m;
	int ret = system (cmd.c_str());
	return (ret == 0);	
}

bool add_module(const string &m)
{
	if (!verify_root()) return false;
	string cmd = "/sbin/modprobe " + m;
	int ret = system (cmd.c_str());
	return (ret == 0);	
}	
#if TEST
int main()
{
	if (query_module("r8169"))
		cout << "found \n";
	else
		 cout << "not found \n";
	
	getchar();
	
	if (remove_module("r8169"))
		cout << "removed \n";
		
	getchar();

	if (add_module("r8169"))
		cout << "added \n";
}
#endif