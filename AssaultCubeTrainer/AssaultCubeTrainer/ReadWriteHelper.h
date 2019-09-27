#pragma once
#include <cstdint>
#include <windows.h>
#include <vector>


void ReadMemory(HANDLE handle, uintptr_t& add);
void WriteMemory(HANDLE handle, uintptr_t& add, int value);

uintptr_t MultiLevelPointer(HANDLE handle, uintptr_t address, const std::vector<uintptr_t>& levels);
