#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "monitor.h"

#define MAX_BUFFER_SIZE 9

int buffer[MAX_BUFFER_SIZE]; // bufro FIFO
int count = 0; // liczba elementów w buforze
int in = 0; // indeks dla producenta
int out = 0; // indeks dla konsumentów

Semaphore mutex_prod(1); // semafor dla producentów
Semaphore mutex_cons(1); // semafor dla konsumentów
Semaphore buffer_count(0); // semafor dla liczby elementów w buforze

void *producer(void *arg)
{
    int item;
    while (true)
    {
        item = rand() % 100; // losowa liczba od 0 do 99
        mutex_prod.p();
        if (count == MAX_BUFFER_SIZE)
        {
            printf("Buffer full\n");
            mutex_prod.v();
            continue;
        }
        buffer[in] = item;
        printf("Producer %d produced %d\n", *((int *)arg), item);
        in = (in + 1) % MAX_BUFFER_SIZE;
        count++;
        mutex_prod.v();
        buffer_count.v();
    }
    pthread_exit(NULL);
}

void *consumer_a(void *arg)
{
    int item;
    while (true)
    {
        buffer_count.p();
        mutex_cons.p();
        item = buffer[out];
        if (count <= 3)
        {
            printf("Buffer empty\n");
            mutex_cons.v();
            buffer_count.v();
            continue;
        }
        if (item % 2 != 0)
        {
            printf("Consumer A skipped %d\n", item);
            mutex_cons.v();
            buffer_count.v();
            continue;
        }
        printf("Consumer A consumed %d\n", item);
        out = (out + 1) % MAX_BUFFER_SIZE;
        count--;
        mutex_cons.v();
    }
    pthread_exit(NULL);
}

void *consumer_b(void *arg)
{
    int item;
    while (true)
    {
        buffer_count.p();
        mutex_cons.p();
        item = buffer[out];
        if (count <= 3)
        {
            printf("Buffer empty\n");
            mutex_cons.v();
            buffer_count.v();
            continue;
        }
        if (item % 2 == 0)
        {
            printf("Consumer B skipped %d\n", item);
            mutex_cons.v();
            buffer_count.v();
            continue;
        }
        printf("Consumer B consumed %d\n", item);
        out = (out + 1) % MAX_BUFFER_SIZE;
        count--;
        mutex_cons.v();
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));

    int prod_id_1 = 1, prod_id_2 = 2;
    int cons_id_a = 1, cons_id_b = 2;

    pthread_t prod_thread_1, prod_thread_2;
    pthread_t cons_thread_a, cons_thread_b;

    pthread_create(&prod_thread_1, NULL, producer, &prod_id_1);
    pthread_create(&prod_thread_2, NULL, producer, &prod_id_2);
    pthread_create(&cons_thread_a, NULL, consumer_a, &cons_id_a);
    pthread_create(&cons_thread_b, NULL, consumer_b, &cons_id_b);

    pthread_join(prod_thread_1, NULL);
    pthread_join(prod_thread_2, NULL);
    pthread_join(cons_thread_a, NULL);

}