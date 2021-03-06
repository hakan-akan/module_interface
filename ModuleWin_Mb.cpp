
#include <driverspecs.h>
#include <windows.h>
#include <Cfgmgr32.h>
#include <Setupapi.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept> // runtime_error
#include <Module_Mb.h>

namespace   Innovative
{

// either string or wstring (_UNICODE)
typedef std::basic_string<TCHAR> tstring;

//------------------------------------------------------------------------------
//  ScanForHardwareChanges -- Utility function to do a refresh
//------------------------------------------------------------------------------

static bool ScanForHardwareChanges()
{
	DEVINST     devInst;
	CONFIGRET   status;
	//
	// Get the root devnode.
	//
	status = CM_Locate_DevNode(&devInst, NULL, CM_LOCATE_DEVNODE_NORMAL);
	if (status != CR_SUCCESS) {
		runtime_error("CM_Locate_DevNode failed.");
		return false;

	}

	status = CM_Reenumerate_DevNode(devInst, 0);
	if (status != CR_SUCCESS) {
		runtime_error("CM_Reenumerate_DevNode failed.");
		return false;
	}

	return true;
}

//------------------------------------------------------------------------------
//  QueryModule -- Checks if the given module loaded
//------------------------------------------------------------------------------

bool QueryModule(const string /*&m*/)
{
	return true;
}

//------------------------------------------------------------------------------
//  RemoveModule -- Removes the given module from the OS
//------------------------------------------------------------------------------

bool RemoveModule(const string &m)
{
	HDEVINFO hDevInfo;
	SP_DEVINFO_DATA DeviceInfoData;

	// Create a HDEVINFO with all present devices.
	hDevInfo = SetupDiGetClassDevs(NULL,
		0, // Enumerator
		0,
		DIGCF_PRESENT | DIGCF_ALLCLASSES);

	if (hDevInfo == INVALID_HANDLE_VALUE)
	{
		// Insert error handling here.
		return false;
	}

	// Enumerate through all devices in Set.
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)
	{
		DWORD  dataT;
		LPTSTR buffer = NULL;
		DWORD  buffersize = 0;

		while (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_DEVICEDESC,
			&dataT,
			(PBYTE)buffer,
			buffersize,
			&buffersize))
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				// Change the buffer size.
				if (buffer) LocalFree(buffer);
				// Double the size to avoid problems on
				buffer = (LPTSTR)LocalAlloc(LPTR, buffersize * 2);
			}
			else
			{
				// Insert error handling here.
				break;
			}
		}

		if (buffersize == 0) continue;

		// if device found change it's state
		if (!wcscmp(m.c_str(), buffer))
		{
			// remove the device
			if (!SetupDiCallClassInstaller(DIF_REMOVE, hDevInfo, &DeviceInfoData)) {
				DWORD errorcode = GetLastError(); // error here
			}
		}

		if (buffer) LocalFree(buffer);
	}

	if (GetLastError() != NO_ERROR &&
		GetLastError() != ERROR_NO_MORE_ITEMS)
	{
		return false;
	}

	//  Cleanup
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return true;
}


//------------------------------------------------------------------------------
//  AddModule -- Adds the given module to the OS
//------------------------------------------------------------------------------

bool AddModule(const string /*&m*/)
{
  // In Windows OS the module is already loaded. We just do a refresh.
	ScanForHardwareChanges();
}


} // namespace
