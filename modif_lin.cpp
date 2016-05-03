#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h> // getuid

using namespace std;

bool verify_root()
{
	if (getuid()) {
		cout << "You must be root to do this!\n";
		return false;
	}
	return true; 	
}
bool query_module(const std::string &m)
{
	if (!verify_root()) return false; 
		
	fstream f("/proc/modules");
	if (!f.is_open())
		cout << "failed opening /proc/modules\n";
		   
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

bool remove_module(const std::string &m)
{
	
}

bool add_module(const std::string &m)
{
	
}

int main()
{
	if (query_module("r8169"))
		cout << "found \n";
	else
		cout << "not found \n";	
}