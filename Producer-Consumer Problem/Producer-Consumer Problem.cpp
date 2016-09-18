#include "stdafx.h"
#include "PCB.h"
#include "Semaphore.h"
#include "Queue.h"
#define BASE_DELAY 500
Semaphore empty(5);
Semaphore full(0);

Queue<unsigned> buffer;
void produce(PCB *p)
{
	while (true)
	{
		unsigned int num;
		unsigned int delay;
		_rdrand32_step(&num);//Generate random data
		_rdrand32_step(&delay);//Generate random thread delay
		num %= 1000;//For Human Reading

		empty.Wait(p);
		buffer.push(num);

		full.Signal();
		std::printf("Process %d Produced %u\n", p->GetPID(), num);//Display
		std::this_thread::sleep_for(std::chrono::milliseconds(delay % 100 + BASE_DELAY));//Delay
	}
}
void consume(PCB *p)
{
	while (true)
	{
		unsigned int num;
		unsigned int delay;
		_rdrand32_step(&delay);

		full.Wait(p);
		num = buffer.pop();

		empty.Signal();
		std::printf("Process %d Consumed %u\n", p->GetPID(), num);
		std::this_thread::sleep_for(std::chrono::milliseconds(delay % 100 + BASE_DELAY));
	}
}
int main()
{
	PCB *p = new PCB;
	PCB *c = new PCB;
	p->Init(produce, 0, p);
	c->Init(consume, 1, c);
	std::this_thread::sleep_for(std::chrono::minutes(10));
	return 0;
}

