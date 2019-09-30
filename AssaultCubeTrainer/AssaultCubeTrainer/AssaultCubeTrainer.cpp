// AssaultCubeTrainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ProcessHelper.h"
#include "ReadWriteHelper.h"

HANDLE handle = nullptr;

struct PlayerEntity
{
	uintptr_t LocalPlayer; //address of our ent
	//int Team;
	int Health;
	float Position[3];
	char Name[32];
	void ReadInformation()
	{
		ReadProcessMemory(handle, reinterpret_cast<BYTE*>(LocalPlayer+0xf8), &Health, sizeof(Health), nullptr);
		ReadProcessMemory(handle, reinterpret_cast<BYTE*>(LocalPlayer + 0x34), &Position, sizeof(Position), nullptr);
		ReadProcessMemory(handle, reinterpret_cast<BYTE*>(LocalPlayer + 0x225), &Name, sizeof(Name), nullptr);

	}
};

int main()
{

	uintptr_t pID = GetProcessID(L"ac_client.exe"); // Since we need only the assaultcube process, I hard coded the process name.

	uintptr_t moduleBase = GetModuleBase(L"ac_client.exe"); // Since we need only the assaultcube process, I hard coded the process name.


    handle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pID);
	if (!handle)
	{
		std::cout << "AssaultCube Process has not been found !" << std::endl;
	}
	else if(handle)
	{
		std::cout << "Open Process succeeded" << std::endl;

		uintptr_t add = 0x00EFA310;
		std::cout << std::hex << add << std::endl;
		ReadMemory(handle, add);

		uintptr_t entity = moduleBase + 0x00109B74;
		std::cout << "Module Base : " << std::hex << moduleBase << " entity " << entity << std::endl;
		const std::vector<uintptr_t> test = { 0x0 };
		uintptr_t player = MultiLevelPointer(handle, entity, test);
		

		std::cout << "Where am I ? : 0x" << std::hex << player << std::endl;

		uintptr_t ammo = player + 0x150;
		ReadMemory(handle, ammo);
		uintptr_t ammoSub = player + 0x13c;

		uintptr_t health = player + 0xf8;

		uintptr_t armor = player + 0xfc;
		//WriteMemory(handle, ammo, 34);

		//vector3<float> hi;

		uintptr_t playerx = player + 0x34;
		uintptr_t playery = player + 0x38;
		uintptr_t playerz = player + 0x3c;

		bool infiniteAmmo = false;
		bool infiniteAmmoSub = false;

		bool infiniteHealth = false;
		bool infiniteArmor = false;

		float x = 0.0f, y = 0.0f, z = 0.0f;

		float sx = 0.0f, sy = 0.0f, sz = 0.0f;


		//PlayerEntity* testing = new PlayerEntity[4];

		//const std::vector<uintptr_t> distanceP = { 0x0 };
		uintptr_t playersEnt = moduleBase + 0x00110D90;
		

		


		PlayerEntity* testEntities = new PlayerEntity[4];
		
		
		uintptr_t dis = 0x0;
		for (int i =0; i<4; ++i)
		{
			const std::vector<uintptr_t> distanceP = { 0x0, 0x0 };
			uintptr_t temp = MultiLevelPointer(handle, playersEnt, distanceP);
			std::cout << "temp : " << std::hex << temp << std::endl;
			testEntities[i].LocalPlayer = temp;
			testEntities[i].ReadInformation();

			std::cout << "info " << testEntities[i].Health << std::endl;
			dis += 0x4;
		}

		
		return 0;
		while(true)
		{
			ReadProcessMemory(handle, reinterpret_cast<BYTE*>(playerx), &x, sizeof(x), nullptr);
			ReadProcessMemory(handle, reinterpret_cast<BYTE*>(playery), &y, sizeof(y), nullptr);
			ReadProcessMemory(handle, reinterpret_cast<BYTE*>(playerz), &z, sizeof(z), nullptr);
			
			system("cls");
			printf("[F1]\t Infinite Ammo [Main] : %d \n", infiniteAmmo);
			printf("[F2]\t Infinite Ammo [Sub] : %d \n", infiniteAmmoSub);
			printf("[F3]\t Infinite Health : %d \n", infiniteHealth);
			printf("[F4]\t Infinite Armor : %d \n", infiniteArmor);
			printf("[F5]\t Teleport to Saved Pos \n");
			printf("[F6]\t Save the Current Pos \n");
			printf("[Player Pox]\t %f %f %f \n", x, y, z);

			if(GetKeyState(VK_F1) & 0x8000)
			{
				infiniteAmmo = !infiniteAmmo;
			}

			if (GetKeyState(VK_F2) & 0x8000)
			{
				infiniteAmmoSub = !infiniteAmmoSub;
			}

			if (GetKeyState(VK_F3) & 0x8000)
			{
				infiniteHealth = !infiniteHealth;
			}

			if (GetKeyState(VK_F4) & 0x8000)
			{
				infiniteArmor = !infiniteArmor;
			}

			if (GetKeyState(VK_F5) & 0x8000)
			{
				if(sx != 0.0f && sy != 0.0f && sz != 0.0f)
				{
					WriteMemory(handle, playerx, sx);
					WriteMemory(handle, playery, sy);
					WriteMemory(handle, playerz, sz);
				}

			}

			if (GetKeyState(VK_F6) & 0x8000)
			{
				sx = x;
				sy = y;
				sz = z;
			}
			
			if(infiniteAmmo)
			{
				WriteMemory(handle, ammo, 34);
			}

			if (infiniteAmmoSub)
			{
				WriteMemory(handle, ammoSub, 34);
			}

			if (infiniteHealth)
			{
				WriteMemory(handle, health, 255);
			}

			if (infiniteArmor)
			{
				WriteMemory(handle, armor, 255);
			}
			
			Sleep(100);
		}
		
		
	}

	CloseHandle(handle); // close the handle to exit program properly
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
