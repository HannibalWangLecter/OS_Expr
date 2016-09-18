#pragma once
#include "stdafx.h"
#include "PCB.h"
#include "Queue.h"

class Semaphore
{
private:
	std::atomic_int value;
	Queue<PCB*> list;
public:
	Semaphore(int val);
	void Wait(PCB *p);
	void Signal();
	~Semaphore();
};