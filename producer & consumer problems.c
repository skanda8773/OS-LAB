#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define buffersize 5

int max_items;
int buffer[buffersize];
int in=0;
int out=0;
sem_t empty,full;
pthread_mutex_t mutex;


void* producer(void* arg)
{
    int item;
    for(int i=0;i<max_items;i++)
    {
        item=rand()%100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in]=item;
        printf("produced: %d at %d\n",item,in);
        in=(in+1)%buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg)
{
    int item;
    for(int i=0;i<max_items;i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        buffer[out]=item;
        printf("consumed: %d from %d\n",item,out);
        out=(out+1)%buffersize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main()
{
    printf("Enter Maximum Items: ");
    scanf("%d",&max_items);
    pthread_t prod,cons;
    sem_init(&empty, 0 , buffersize);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,full);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
