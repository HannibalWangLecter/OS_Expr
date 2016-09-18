#include "stdafx.h"
#include "PCB.h"


void PCB::Init(void(*f)(PCB *), int PID, PCB *current)
{
	thread = new std::thread(f, current);
	this->PID = PID;
}

void PCB::Block()
{
	isBlocking = true;
	std::printf("Blocking Thread %d\n", PID);//Print message
	//Set isBlocking to true to do infinite loop
	while (isBlocking)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(20));//Sleep current thread for 20 ms
	}
}

void PCB::Active()
{
	std::printf("Activating Thread %d\n", PID);
	isBlocking = false;//Set isBlocking to false to end loop in next execution
}

int PCB::GetPID()
{
	return PID;
}


PCB::~PCB()
{
	delete thread;
}