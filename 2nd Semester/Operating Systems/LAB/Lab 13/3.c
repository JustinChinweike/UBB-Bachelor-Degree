#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int to_guess;
int winner = -1;

pthread_mutex_t m;
pthread_cond_t c;

void *guesser(void *arg) {
    int id = *((int *) arg);
    while(1) {
        pthread_mutex_lock(&m);
        if(winner != -1) {
            pthread_mutex_unlock(&m);
            break;
        }
        int guess = rand() % 1000;
        printf("Thread %3d guessed %4d - target %4d\n", id, guess, to_guess);
        if(guess == to_guess) {
            winner = id;
            pthread_cond_signal(&c);
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *announcer(void *arg) {
    pthread_mutex_lock(&m);
    while(winner == -1)
        pthread_cond_wait(&c, &m);

    printf("The winner was thread %d\n", winner);

    pthread_mutex_unlock(&m);
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please provide the number of threads!\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    pthread_t th[n + 1];
    int *ids = malloc(sizeof(int) * n);
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);
    srand(getpid());
    to_guess = rand() % 1000;
    for(int i = 0; i < n; i++) {
        ids[i] = i;
        if(0 != pthread_create(&th[i], NULL, guesser, &ids[i])) {
            perror("Error creating thread");
        }
    }
    if(0 != pthread_create(&th[n], NULL, announcer, NULL)) {
        perror("Error creating announcer thread");
    }
    for(int i = 0; i < n + 1; i++) {
        pthread_join(th[i], NULL);
    }
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    free(ids);

    return 0;
}