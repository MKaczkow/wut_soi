#include <iostream>
#include <string>
#include "monitor.h"

int const threadsCounts = 4;  //liczba wątków

// int const numberOfLettersA = 20;
// int const numberOfLettersB = 20;

std::string s;

Semaphore semConsumerOdd(2);
Semaphore semConsumerEven(1);
Semaphore semProducer(3);

// void writeA()
// {
// 	semA.p();
// 	std::cout << "A" << std::flush;
// 	s += "A";
// 	semB.v();

// }

// void writeB()
// {
// 	semB.p();
// 	std::cout << "B" << std::flush;
// 	s += "B";
// 	semA.v();
// }

// void* threadA(void* arg)
// {
// 	for (int i = 0; i < numberOfLettersA; ++i)
// 	{
// 		writeA();
// 	}
// 	return NULL;
// }

// void* threadB(void* arg)
// {
// 	for (int i = 0; i < numberOfLettersB; ++i)
// 	{
// 		writeB();
// 	}
// 	return NULL;
// }

void produce()
{
	semProducer.p();
	std::cout << "p" << std::flush;
	// s += "B";
	semProducer.v();
}

void consumeEven()
{
	semConsumerEven.p();
	std::cout << "e" << std::flush;
	// s += "A";
	semConsumerEven.v();
}

void consumeOdd()
{
	semConsumerOdd.p();
	std::cout << "o" << std::flush;
	// s += "A";
	semConsumerOdd.v();
}

void* threadFirstProducer(void* arg)
{
	// std::cout << 'c' << std::endl;
	for (int i = 0; i < 19; ++i)
	{
		produce();
	}
	return NULL;
}

void* threadSecondProducer(void* arg)
{
	// std::cout << 'c' << std::endl;
	for (int i = 0; i < 19; ++i)
	{
		produce();
	}
	return NULL;
}

void* threadFirstConsumer(void* arg)
{
	// std::cout << 'p' << std::endl;
	for (int i = 0; i < 19; ++i)
	{
		consumeEven();
	}
	return NULL;
}

void* threadSecondConsumer(void* arg)
{
	// std::cout << 'p' << std::endl;
	for (int i = 0; i < 19; ++i)
	{
		consumeOdd();
	}
	return NULL;
}

int main()
{
#ifdef _WIN32
	std::cout << "Windows??";
	std::cout << "\n";
	HANDLE tid[threadsCounts];
	DWORD id;

	// utworzenie wątków
	tid[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFirstProducer, 0, 0, &id);
	tid[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSecondProducer, 0, 0, &id);
	tid[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadFirstConsumer, 0, 0, &id);
	tid[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadSecondConsumer, 0, 0, &id);

	// czekaj na zakończenie wątków
	for (int i = 0; i <= threadsCounts; i++)
		WaitForSingleObject(tid[i], INFINITE);
#else
	std::cout << "Non-Windows??";
	std::cout << "\n";
	pthread_t tid[threadsCounts];

	// utworzenie wątków
	// pthread_create(&(tid[0]), NULL, threadA, NULL);
	// pthread_create(&(tid[1]), NULL, threadB, NULL);
	pthread_create(&(tid[0]), NULL, threadFirstProducer, NULL);
	pthread_create(&(tid[1]), NULL, threadSecondProducer, NULL);
	pthread_create(&(tid[2]), NULL, threadFirstConsumer, NULL);
	pthread_create(&(tid[3]), NULL, threadSecondConsumer, NULL);

	//czekaj na zakoączenie wątków
	for (int i = 0; i < threadsCounts; i++)
		pthread_join(tid[i], (void**)NULL);
#endif
	std::cout << "\n";
	// std::cout << "s=" << s << "\n";
	return 0;
}

