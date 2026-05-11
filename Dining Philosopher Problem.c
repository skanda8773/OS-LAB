#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t *chopsticks;
int NUM_PHILOSOPHERS;
int TIME_SLICE;

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < 2; i++) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % TIME_SLICE + 1);
        if (id % 2 == 0) {
            pthread_mutex_lock(&chopsticks[left_chopstick]);
            pthread_mutex_lock(&chopsticks[right_chopstick]);
        } else {
            pthread_mutex_lock(&chopsticks[right_chopstick]);
            pthread_mutex_lock(&chopsticks[left_chopstick]);
        }
        printf("Philosopher %d is EATING.\n", id);
        sleep(rand() % TIME_SLICE + 1);

        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
        printf("Philosopher %d finished eating.\n", id);
    }
    return NULL;
}
int main() {
    printf("Enter number of philosophers: ");
    scanf("%d", &NUM_PHILOSOPHERS);
    printf("Enter time slice (in seconds): ");
    scanf("%d", &TIME_SLICE);
    pthread_t *philosophers = malloc(NUM_PHILOSOPHERS * sizeof(pthread_t));
    int *ids = malloc(NUM_PHILOSOPHERS * sizeof(int));
    chopsticks = malloc(NUM_PHILOSOPHERS * sizeof(pthread_mutex_t));
    srand(time(NULL));
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    free(philosophers);
    free(ids);
    free(chopsticks);
    printf("All philosophers have finished dining.\n");
    return 0;
}
