#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    if(0 != mkfifo(myfifo1, 0600)) {
        error(1, errno, "Error creating fifo %s", myfifo1);
    }
    if(0 !=  mkfifo(myfifo2, 0600)) {
        unlink(myfifo1);
        error(1, errno, "Error creating fifo %s", myfifo2);
    }

    int a2b = open(myfifo1, O_WRONLY);
    if (-1 == a2b) {
        unlink(myfifo1);
        unlink(myfifo2);
        error(1, errno, "Error opening fifo %s in write mode", myfifo1);
    }
    int b2a = open(myfifo2, O_RDONLY);
    if (0 > b2a) {
        close(a2b);
        unlink(myfifo1);
        unlink(myfifo2);
        error(1, errno, "Error opening fifo %s in read mode", myfifo2);
    }
    srand(getpid());
    int n = rand() % 1000 + 1;
    int response = 0, guess = 0, count = 0, k;
    printf("Generated: %d\n", n);
    do {
        if(0 != (k = read(b2a, &guess, sizeof(int)))) {
            if(-1 == k) {
                error(0, errno, "Error reading number");
                break;
            }
        }
        count++;
        printf("Attempt %2d -> target: %4d - received: %4d\n", count, n, guess);
        if(n == guess) {
            response = 0;
        } else if (n > guess) {
            response = -1;
        } else {
            response = 1;
        }
        if(0 != (k = write(a2b, &response, sizeof(int)))) {
            if(-1 == k) {
                error(0, errno, "Error sending response");
                break;
            }
        }
    } while (response != 0);
    close(a2b);
    close(b2a);
    if(0 != unlink(myfifo1)) {
        error(0, errno, "Error removing fifo %s", myfifo1);
    }
    if(0 != unlink(myfifo2)) {
        error(0, errno, "Error removing fifo %s", myfifo2);
    }

    return 0;
}