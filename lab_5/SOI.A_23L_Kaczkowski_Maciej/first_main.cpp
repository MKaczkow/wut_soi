#include <iostream>
#include <vector>
#include <string>
#include "monitor.h"
#include <time.h>
#include <stdlib.h>

int const threadsCounts = 4; // liczba wątków

int const bufferSize = 9;

class Buffer
{
private:
	Semaphore mutex;
	Semaphore empty;
	Semaphore full;
	Semaphore semEven;
	Semaphore semOdd;

	std::vector<int> values;

	void print(std::string name)
	{
		std::cout << "\n"
				  << name << " "
				  << "[";
		for (auto v : values)
			std::cout << v << ",";
		std::cout << "] \n";
	}

public:
	Buffer() : mutex(1), empty(0), full(bufferSize), semEven(0), semOdd(0)
	{
	}

	void putA(int value)
	{

		// first item => set semEven or semOdd
		if (sizeof(values) == 0) {
			if (value % 2 == 0) {
				semEven.v();
			}
			else {
				semOdd.v();
			}
		}
		full.p();
		mutex.p();
		values.push_back(value);
		print("A production");

		if (sizeof(values) / sizeof(value) > 3)
		{
			empty.v();
		}
		mutex.v();
	}

	void putB(int value)
	{
		// first item => set semEven or semOdd
		if (sizeof(values) == 0) {
			if (value % 2 == 0) {
				semEven.v();
			}
			else {
				semOdd.v();
			}
		}
		full.p();
		mutex.p();
		values.push_back(value);
		print("B production");

		if (sizeof(values) / sizeof(value) > 3)
		{
			empty.v();
		}
		mutex.v();
	}

	int getEven()
	{
		semEven.p();
		empty.p();
		mutex.p();

		auto value = values.front();
		values.erase(values.begin());
		auto nextValue = values.front();
		if (nextValue % 2 == 0)
		{
			semEven.v();
		}
		else
		{
			semOdd.v();
		}

		print("Even consumption");

		full.v();
		mutex.v();
		return value;
	}

	int getOdd()
	{
		semOdd.p();
		empty.p();
		mutex.p();

		auto value = values.front();
		values.erase(values.begin());
		auto nextValue = values.front();
		if (nextValue % 2 == 0)
		{
			semEven.v();
		}
		else
		{
			semOdd.v();
		}

		print("Odd consumption");

		full.v();
		mutex.v();
		return value;
	}
};

Buffer buffer;

void *threadProdA(void *arg)
{
	for (int i = 0; i < 20; ++i)
	{
		int val = rand() % 10;
		buffer.putA(val);
	}
	return NULL;
}

void *threadProdB(void *arg)
{
	for (int i = 0; i < 20; ++i)
	{
		int val = rand() % 10;
		buffer.putB(val);
	}
	return NULL;
}

void *threadConsEven(void *arg)
{
	for (int i = 0; i < 20; ++i)
	{
		auto value = buffer.getEven();
	}
	return NULL;
}

void *threadConsOdd(void *arg)
{
	for (int i = 0; i < 20; ++i)
	{
		auto value = buffer.getOdd();
	}
	return NULL;
}

int main()
{
#ifdef _WIN32
	HANDLE tid[threadsCounts];
	DWORD id;
	srand(time(NULL)); // Initialization, should only be called once.

	// utworzenie wątków
	tid[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProdA, 0, 0, &id);
	tid[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProdB, 0, 0, &id);
	tid[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadConsEven, 0, 0, &id);
	tid[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadConsOdd, 0, 0, &id);

	// czekaj na zakończenie wątków
	for (int i = 0; i <= threadsCounts; i++)
		WaitForSingleObject(tid[i], INFINITE);
#else
	pthread_t tid[threadsCounts];
	srand(time(NULL)); // Initialization, should only be called once.

	// utworzenie wątków
	pthread_create(&(tid[0]), NULL, threadProdA, NULL);
	pthread_create(&(tid[1]), NULL, threadProdB, NULL);
	pthread_create(&(tid[2]), NULL, threadConsEven, NULL);
	pthread_create(&(tid[3]), NULL, threadConsOdd, NULL);

	// czekaj na zakończenie wątków
	for (int i = 0; i < threadsCounts; i++)
		pthread_join(tid[i], (void **)NULL);
#endif
	return 0;
}