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



uintptr_t MultiLevelPointer(HANDLE handle, uintptr_t address, const std::vector<uintptr_t>& levels)
{
	//std::cout << "level " << levels.size() << std::endl;
	uintptr_t result = address;
	
	for (uintptr_t add : levels)
	{
		ReadProcessMemory(handle, reinterpret_cast<BYTE*>(result), &result, sizeof(result), nullptr);
		//std::cout << "inside " << std::hex << result << std::endl;
		result += add;
	}
	return result;
}

