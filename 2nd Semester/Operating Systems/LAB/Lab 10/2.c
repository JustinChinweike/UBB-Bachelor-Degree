#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <error.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Please provide at least one argument!\n");
        exit(1);
    }
    int size = argc - 1;
    int p[size][2];
    for(int i = 0; i < size; i++) {
        if(0 != pipe(p[i])) {
            error(1, errno, "Error when creating pipe %d\n", i);
        }
    }
    for(int i = 0; i < size; i++) {
        int f = fork();
        if(-1 == f) {
            error(1, errno, "Error creating child process %d\n", i);
        } else if (0 == f) {
            for(int j = 0; j < size; j++) {
                if(i != j) {
                    close(p[j][0]);
                    close(p[j][1]);
                }
            }
            close(p[i][0]);
            int l = 0, d = 0, k;
            for(int j = 0; j < strlen(argv[i+1]); j++) {
                if(isalpha(argv[i+1][j])) {
                    l++;
                } else if (isdigit(argv[i+1][j])) {
                    d++;
                }
            }
            if(0 != (k = write(p[i][1], &l, sizeof(int)))) {
                if(-1 == k) {
                    close(p[i][1]);
                    error(1, errno, "Error writing letter count from child %d\n", i);
                }
            }
            if(0 != (k = write(p[i][1], &d, sizeof(int)))) {
                if(-1 == k) {
                    close(p[i][1]);
                    error(1, errno, "Error writing digit count from child %d\n", i);
                }
            }
            close(p[i][1]);
            exit(0);
        }
    }
    int total_l = 0, total_d = 0;
    int k;
    for(int i = 0; i < size; i++) {
        int l = 0, d = 0;
        close(p[i][1]);
        if(0 != (k = read(p[i][0], &l, sizeof(int)))) {
            if(-1 == k) {
                close(p[i][0]);
                error(0, errno, "Error reading letter count from child %d", i);
            }
        }
        if(0 != (k = read(p[i][0], &d, sizeof(int)))) {
            if(-1 == k) {
                close(p[i][0]);
                error(0, errno, "Error reading digit count from child %d", i);
            }
        }
        total_l += l;
        total_d += d;
        close(p[i][0]);
    }

    for(int i = 0; i < size; i++) {
        wait(NULL);
    }

    printf("Letters: %d\nDigits: %d\n", total_l, total_d);
    return 0;
}