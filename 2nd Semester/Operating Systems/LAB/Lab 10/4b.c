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
    int a2b = open(myfifo1, O_RDONLY);
    if (-1 == a2b) {
        error(1, errno, "Error opening fifo %s in read mode", myfifo1);
    }
    int b2a = open(myfifo2, O_WRONLY);
    if (0 > b2a) {
        close(a2b);
        error(1, errno, "Error opening fifo %s in write mode", myfifo2);
    }
    srand(getpid());
    int response = 0, guess = 0, count = 0, k;
    int min = 1, max = 1000;
    do {
        guess = rand() % (max - min + 1) + min;
        count++;
        printf("Attempt %2d -> guess: %4d within the bounds [%4d, %4d]\n", count, guess, min, max);
        if(0 != (k = write(b2a, &guess, sizeof(int)))) {
            if(-1 == k) {
                error(0, errno, "Error sending guess");
                break;
            }
        }
        if(0 != (k = read(a2b, &response, sizeof(int)))) {
            if(-1 == k) {
                error(0, errno, "Error reading response");
                break;
            }
        }

        if(0 == response) {
            printf("Guessed correctly after %d attempts\n", count);
        } else if (-1 == response) {
            min = guess + 1;
        } else {
            max = guess - 1;
        }
    } while (response != 0);
    close(a2b);
    close(b2a);
    return 0;
}
