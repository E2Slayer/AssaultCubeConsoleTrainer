#pragma once
#include <cstdint>
#include <windows.h>
#include <vector>


void ReadMemory(HANDLE handle, uintptr_t& add);
template<typename T>
void WriteMemory(HANDLE handle, uintptr_t& add, T value)
{
	DWORD oldProtection = 0;
	VirtualProtectEx(handle, reinterpret_cast<BYTE*>(add), sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtection);
	WriteProcessMemory(handle, reinterpret_cast<BYTE*>(add), &value, sizeof(value), nullptr);
	VirtualProtectEx(handle, reinterpret_cast<BYTE*>(add), sizeof(value), oldProtection, nullptr);

}

uintptr_t MultiLevelPointer(HANDLE handle, uintptr_t address, const std::vector<uintptr_t>& levels);
