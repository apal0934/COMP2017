#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>


#define THINKERS 5
sem_t sema;

void* dine(void* arg) {
    const unsigned id = *((unsigned *) arg);
    while (true) {
        // the ith philosopher can only reach
        // the ith and (i + 1)th chopstick
        sem_wait(&sema);
        printf("Philosopher %u is eating\n", id);
        sem_post(&sema);
    }
    return NULL;
}

int main(void) {
    unsigned args[THINKERS];
    pthread_t thinkers[THINKERS];
    
    // create the chopsticks
    sem_init(&sema, 0, 5);
    
    // launch threads
    for (size_t i = 0; i < THINKERS; i++) {
        args[i] = i;
        if (pthread_create(thinkers + i, NULL, dine, args + i) != 0) {
            perror("unable to create thread");
            return 1;
        }
    }
    
    // wait for threads to finish
    for (size_t i = 0; i < THINKERS; i++) {
        if (pthread_join(thinkers[i], NULL) != 0) {
            perror("unable to join thread");
            return 1;
        }
    }
    
    return 0;
}
