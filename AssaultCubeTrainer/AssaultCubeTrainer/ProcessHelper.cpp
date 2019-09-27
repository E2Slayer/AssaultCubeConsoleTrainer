#include "ProcessHelper.h"
#include <cstdint>
#include <TlHelp32.h>
#include <windows.h>
#include <iostream>

uintptr_t GetProcessID(const wchar_t* modName)
{
	DWORD processID = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "[ERROR] Process name is not valid, Please check it again" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "[Success] The Process ID has been acquired" << std::endl;
		PROCESSENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Process32First(hSnap, &modEntry))
		{
			do
			{
				if (_wcsicmp(modEntry.szExeFile, modName) == 0)
				{
					processID = DWORD(modEntry.th32ProcessID);
					break;
				}
			} while (Process32Next(hSnap, &modEntry));
		}

	}
	CloseHandle(hSnap);
	return processID;
}

uintptr_t GetModuleBase(const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetProcessID(modName));

	if (hSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "[ERROR] Process name or Process id is not valid, Please check it again" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "[Success] The process handle has been acquired" << std::endl;
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (_wcsicmp(modEntry.szModule, modName) == 0)
				{
					modBaseAddr = uintptr_t(modEntry.modBaseAddr);
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}

	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

