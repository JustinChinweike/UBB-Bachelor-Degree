#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
pthread_mutex_t mtx;
int s = 0;

void *f(void *arg) {
    int id = *((int*) arg);
    while(1) {
        int val = rand() % 1001 - 500;
        pthread_mutex_lock(&mtx);
        if(abs(s) > 5000) {
            pthread_mutex_unlock(&mtx);
            break;
        }
        s += val;
        printf("Thread %d generated %d; new value: %d\n", id, val, s);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("no\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    pthread_t th[n];
    int args[n];
    srand(getpid());
    pthread_mutex_init(&mtx, NULL);
    for(int i = 0; i < n; i++) {
        args[i] = i;
        if(0 != pthread_create(&th[i], NULL, f, &args[i])) {
            perror("Error creating thread");
        }
    }
    for(int i = 0; i < n; i++) {
        if(0 != pthread_join(th[i], NULL)) {
            perror("Horror");
        }
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}