#ifndef Module_MbH
#define Module_MbH


namespace Innovative
{
#ifdef __CLR_VER
#pragma managed(push, off)
#endif

bool QueryModule(const string &m);
bool RemoveModule(const string &m);
bool AddModule(const string &m);

#ifdef __CLR_VER
#pragma managed(pop)
#endif
} // namespace Innovative

#endif
