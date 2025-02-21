#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int id;
    int *arr;
    int size;
    pthread_mutex_t *mtx;
    pthread_barrier_t *bar;
} data;

void *f (void *arg) {
    data a = *((data*) arg);
    printf("Thread %d: ", a.id);
    for(int i = 0; i < a.size; i++) {
        a.arr[i] = rand() % 101;
        printf("%4d", a.arr[i]);
    }
    printf("\n");
    pthread_barrier_wait(a.bar);
    return NULL;
}

void *g(void *arg) {
    data a = *((data*) arg);
    int lv = 0;
    pthread_barrier_wait(a.bar);
    for(int i = 0; i < a.size; i++) {
        pthread_mutex_lock(a.mtx);
        if(a.arr[i] > 0) {
            lv += a.arr[i];
            a.arr[i] = 0;
        }
        pthread_mutex_unlock(a.mtx);
        usleep(10 * 1000);
    }
    printf("Thread %d - value %d\n", a.id, lv);
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please provide one argument\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    srand(getpid());
    pthread_t th[3];
    data args[3];
    int *arr = malloc(sizeof(int) * 10);
    pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mtx, NULL);
    pthread_barrier_t bar;
    pthread_barrier_init(&bar, NULL, 3);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            args[j].id = j;
            args[j].arr = arr;
            args[j].size = 10;
            args[j].mtx = mtx;
            args[j].bar = &bar;
        }
        pthread_create(&th[0], NULL, f, &args[0]);
        pthread_create(&th[1], NULL, g, &args[1]);
        pthread_create(&th[2], NULL, g, &args[2]);

        pthread_join(th[0], NULL);
        pthread_join(th[1], NULL);
        pthread_join(th[2], NULL);
    }
    free(arr);
    free(mtx);
    return 0;
}