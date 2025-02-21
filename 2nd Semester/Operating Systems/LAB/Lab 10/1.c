#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <errno.h>
int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please provide one filename!\n");
        exit(1);
    }
    int p[2];
    if(0 != pipe(p)) {
        error(1, errno, "Error creating pipe");
    }
    int f = fork();
    if(-1 == f) {
        error(1, errno, "Error creating child process");
    } else if (0 == f) {
        close(p[0]);
        FILE *file = fopen(argv[1], "r");
        if(NULL == file) {
            close(p[1]);
            error(1, errno, "Error opening file");
        }
        int n, k;
        if(1 != fscanf(file, "%d", &n)) {
            fclose(file);
            close(p[1]);
            error(1, errno, "Error reading n from the file");
        }
        int * arr = malloc(sizeof(int) * n);
        for(int i = 0; i < n; i++) {
            if(1 != fscanf(file, "%d", &arr[i])) {
                free(arr);
                fclose(file);
                close(p[1]);
                error(1, errno, "Error reading number from the file");
            }
        }
        fclose(file);
        if(0 != (k = write(p[1], &n, sizeof(int)))) {
            if(-1 == k) {
                free(arr);
                close(p[1]);
                error(1, errno, "Error writing n from the pipe");
            }
        }
        if(0 != (k = write(p[1], arr, n * sizeof(int)))) {
            if(-1 == k) {
                free(arr);
                close(p[1]);
                error(1, errno, "Error writing array from the pipe");
            }
        }
        free(arr);
        close(p[1]);
        exit(0);
    }
    int status, exit_code;
    wait(&status);
    close(p[1]);
    if(WIFEXITED(status) && 0 == (exit_code = WEXITSTATUS(status))) {
        int n, k;
        if(0 != (k = read(p[0], &n, sizeof(int)))) {
            if(-1 == k) {
                close(p[0]);
                wait(NULL);
                error(1, errno, "Error reading n from the pipe");
            }
        }
        int count = 0;
        while(n > 0) {
            int nr;
            printf("How many numbers do you want? (Available: %d)\n", n);
            scanf("%d", &count);
            if(count <= 0) {
                break;
            }
            count = count <= n ? count : n;
            n -= count;
            printf("Your numbers are: ");
            for(int i = 0; i < count; i++) {
                if(0 != (k = read(p[0], &nr, sizeof(int)))) {
                    if(-1 == k) {
                        close(p[0]);
                        wait(NULL);
                        error(1, errno, "Error reading number");
                    }
                    printf("%d ", nr);
                }
            }
            printf("\n");
        }
        if (count <= 0) {
            printf("User entered %d. Terminating process!\n", count);
        } else {
            printf("No more numbers are available!\n");
        }
    } else {
        printf("Child process terminated with exit code: %d. Terminating!\n", exit_code);
    }
    close(p[0]);
    return 0;
}