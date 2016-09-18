#pragma once
template <class T>
class Queue
{
private:
	std::queue<T> q;
	std::mutex mutex;
public:
	T pop()
	{
		mutex.lock();
		T item = q.front();
		q.pop();
		mutex.unlock();
		return item;
	}
	void push(T & item)
	{
		mutex.lock();
		q.push(item);
		mutex.unlock();
	}

};
