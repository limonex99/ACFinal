#include <Windows.h>
#include <iostream>
#include <thread>
#include <TlHelp32.h>
#include "SlimMem.h"
#include "offsets.h"																																																																


using namespace std;

/* Defining Slimmem */
SlimUtils::SlimMem mem;
DWORD pid;


/* First definition of cheat functions */
void hp();
void armor();				
void arammo();
void gunammo();
void playerspeed();

/* Booleans for the functions */
bool hpbool = false;
bool armorbool = false;
bool arammobool = false;
bool gunammobool = false;
bool playerspeedbool = false;



void outputRunningFeatures()
{
	system("cls");

	cout << "Welcome to limonex99's Assault Cube Cheat!" << endl << endl;
	cout << "Current Features:" << endl << endl;
	cout << "HP                      (press : NUM1)" << endl;
	cout << "Armor                   (press : NUM2)" << endl;
	cout << "Unlimited Ar Ammos      (press : NUM3)" << endl;
	cout << "Unlimited Gun Ammos     (press : NUM4)" << endl << endl;

	cout << "Created by limonex99" << endl << endl << endl;

	cout << "HP:               " << hpbool << endl;
	cout << "Armor:            " << armorbool << endl;
	cout << "ArAmmo:           " << arammobool << endl;
	cout << "PistolAmmo:       " << gunammobool << endl;
}


void functionTriggers()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_NUMPAD1))
		{
			if (hpbool == true)
			{
				hpbool = false;
				outputRunningFeatures();
			}
			else
			{
				hpbool = true;
				outputRunningFeatures();
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD2))
		{
			if (armorbool == true)
			{
				armorbool = false;
				outputRunningFeatures();
			}
			else
			{
				armorbool = true;
				outputRunningFeatures();
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD3))
		{
			if (arammobool == true)
			{
				arammobool = false;
				outputRunningFeatures();
			}
			else
			{
				arammobool = true;
				outputRunningFeatures();
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD4))
		{
			if (gunammobool == true)
			{
				gunammobool = false;
				outputRunningFeatures();
			}
			else
			{
				gunammobool = true;
				outputRunningFeatures();
			}
		}
		Sleep(300);
	}
}


void funcs()
{
	while (true)
	{
		//Obtaining dynamic PlayerBase
		int dynamicplayer = mem.Read<DWORD>(PlayerBase);
		/* HP */
		if (hpbool == true)
		{
			
			/* writing memory to get 100 hp*/
			mem.Write(dynamicplayer + HP, 100);
		}
		/* Armor */
		if (armorbool == true)
		{

			/* writing memory to get 100 armor*/
			mem.Write(dynamicplayer + Armor, 100);
		}
		/* Ar Ammmos */
		if (arammobool == true)
		{
		

				mem.Write(dynamicplayer + ArAmmo, 30);
			
		}
		/* Ar Ammmos */
		if (gunammobool == true)
		{
			

				mem.Write(dynamicplayer + GunAmmo, 10);
			
		}
		/* Reduce CPU usage */
		Sleep(1);
	}
}


/* Main Function */
int main()
{
	
	

	std::cout << "Waiting for process..." << std::endl;
	while (!SlimUtils::SlimMem::GetPID(L"ac_client.exe", &pid))
		Sleep(500);

	std::cout << "Opening process..." << std::endl;
	if (!mem.Open(pid, SlimUtils::ProcessAccess::Full))
	{
		std::cout << "Failed to open process, error-code: " << GetLastError() << std::endl;
		return 0;
	}
	std::cout << ">Success" << std::endl;

	auto mod = mem.GetModule(L"ac_client.exe");
	if (mod == nullptr) {
		std::cout << "Couldn't find module \"ac_client.exe\"!" << std::endl;
	}
	else {
		std::cout << "\"ac_client.exe\":" <<
			" Base=0x" << std::hex << mod->ptrBase <<
			" Size=0x" << std::hex << mod->dwSize << std::endl;

		/* Defining Threads	*/
		thread t1(functionTriggers);
		thread t2(funcs);
		/* Display the current state in console */
		outputRunningFeatures();

		/* Start Threads */
		t1.join();
		t2.join();
	}
}