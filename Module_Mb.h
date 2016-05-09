#ifndef Module_MbH
#define Module_MbH
#include <string>

namespace Innovative
{
#ifdef __CLR_VER
#pragma managed(push, off)
#endif

bool QueryModule(const std::string &m);
bool RemoveModule(const std::string &m);
bool AddModule(const std::string &m);

#ifdef __CLR_VER
#pragma managed(pop)
#endif
} // namespace Innovative

#endif
