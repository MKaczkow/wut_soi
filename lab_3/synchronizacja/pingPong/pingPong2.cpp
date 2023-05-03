#include <iostream>
#include <string>
#include "monitor.h"

int const threadsCounts = 2;  //liczba wątków

int const numberOfLettersA = 20;
int const numberOfLettersB = 20;

std::string s;

Semaphore semA(1);
Semaphore semB(0);

void writeA()
{
	semA.p();
	std::cout << "A" << std::flush;
	s += "A";
	semB.v();

}

void writeB()
{
	semB.p();
	std::cout << "B" << std::flush;
	s += "B";
	semA.v();
}

void* threadA(void* arg)
{
	for (int i = 0; i < numberOfLettersA; ++i)
	{
		writeA();
	}
	return NULL;
}

void* threadB(void* arg)
{
	for (int i = 0; i < numberOfLettersB; ++i)
	{
		writeB();
	}
	return NULL;
}

int main()
{
#ifdef _WIN32
	HANDLE tid[threadsCounts];
	DWORD id;

	// utworzenie wątków
	tid[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadA, 0, 0, &id);
	tid[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadB, 0, 0, &id);

	// czekaj na zakończenie wątków
	for (int i = 0; i <= threadsCounts; i++)
		WaitForSingleObject(tid[i], INFINITE);
#else
	pthread_t tid[threadsCounts];

	// utworzenie wątków
	pthread_create(&(tid[0]), NULL, threadA, NULL);
	pthread_create(&(tid[1]), NULL, threadB, NULL);

	//czekaj na zakoączenie wątków
	for (int i = 0; i < threadsCounts; i++)
		pthread_join(tid[i], (void**)NULL);
#endif
	std::cout << "\n";
	std::cout << "s=" << s << "\n";
	return 0;
}

