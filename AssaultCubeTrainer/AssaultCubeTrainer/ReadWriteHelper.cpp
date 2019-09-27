#include "ReadWriteHelper.h"
#include <iostream>


void ReadMemory(HANDLE handle, uintptr_t& add)
{
	int value = 0;
	if (ReadProcessMemory(handle, reinterpret_cast<BYTE*>(add), &value, sizeof(value), nullptr))
	{
		std::cout << "Read " << value << std::endl;
	}
	else
	{
		std::cout << "Read Failed" << std::endl;
	}
}

void WriteMemory(HANDLE handle, uintptr_t& add, int value)
{
	DWORD oldProtection = 0;
	VirtualProtectEx(handle, reinterpret_cast<BYTE*>(add), sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtection);
	WriteProcessMemory(handle, reinterpret_cast<BYTE*>(add), &value, sizeof(value), false);
	VirtualProtectEx(handle, reinterpret_cast<BYTE*>(add), sizeof(value), oldProtection, nullptr);

}

uintptr_t MultiLevelPointer(HANDLE handle, uintptr_t address, const std::vector<uintptr_t>& levels)
{
	std::cout << "level " << levels.size() << std::endl;
	uintptr_t result = 0;
	
	for (uintptr_t add : levels)
	{
		ReadProcessMemory(handle, reinterpret_cast<BYTE*>(address), &result, sizeof(result), nullptr);
		std::cout << "inside " << std::hex << result << std::endl;
		result += add;
	}
	return result;
}

