#include "stdafx.h"
#include "Semaphore.h"


Semaphore::Semaphore(int val)
{
	value = val;
}

void Semaphore::Wait(PCB *p)
{
	value--;
	if (value < 0)
	{
		list.push(p);
		p->Block();
	}
}

void Semaphore::Signal()
{
	value++;
	if (value <= 0)
	{
		list.pop()->Active();
	}
}


Semaphore::~Semaphore()
{
}