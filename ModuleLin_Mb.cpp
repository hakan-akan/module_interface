#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>  // getuid
#include <stdexcept> // runtime_error
#include <stdlib.h>
#include <Module_Mb.h>

namespace   Innovative
{

using namespace std;

//------------------------------------------------------------------------------
//  verify_root -- Utility function to ensure root access
//------------------------------------------------------------------------------

static bool verify_root()
{
	if (getuid()) {
		runtime_error("You must be root to do this!");
		return false;
	}
	return true;
}

//------------------------------------------------------------------------------
//  QueryModule -- Checks if the given module loaded
//------------------------------------------------------------------------------

bool QueryModule(const string &m)
{
	if (!verify_root()) return false;
	fstream f("/proc/modules");
	if (!f.is_open()) {
		runtime_error("Failed opening /proc/modules");
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

//------------------------------------------------------------------------------
//  RemoveModule -- Removes the given module from the OS
//------------------------------------------------------------------------------

bool RemoveModule(const string &m)
{
	if (!verify_root()) return false;
	string cmd = "/sbin/rmmod " + m;
	int ret = system (cmd.c_str());
	return (ret == 0);
}

//------------------------------------------------------------------------------
//  AddModule -- Adds the given module to the OS
//------------------------------------------------------------------------------

bool AddModule(const string &m)
{
	if (!verify_root()) return false;
	string cmd = "/sbin/modprobe " + m;
	int ret = system (cmd.c_str());
	return (ret == 0);
}

} // namespace
