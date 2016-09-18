#pragma once
#include "stdafx.h"
class PCB
{
private:
	std::thread *thread;
	int PID;
	std::atomic_bool isBlocking;
public:
	void Init(void(*f)(PCB *), int PID, PCB * current);
	void Block();
	void Active();
	int GetPID();
	~PCB();
};