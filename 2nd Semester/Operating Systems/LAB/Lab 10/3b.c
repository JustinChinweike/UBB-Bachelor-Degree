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
    if (-1 == b2a) {
        close(a2b);
        error(1, errno, "Error opening fifo %s in write mode", myfifo2);
    }
    srand(getpid());
    char *s = malloc(sizeof(char) * 101);
    int len, k;
    do {
        if(0 != (k = read(a2b, &len, sizeof(int)))) {
            if(-1 == k) {
                error(0, errno, "Error reading string length %d", len);
                break;
            }
        }

        if(len == 0)
            break;

        if(0 != (k = read(a2b, s, sizeof(char) * len))) {
            if(-1 == k) {
                error(0, errno, "Error reading string %s", s);
                break;
            }
        }

        s[len] = 0;
        printf("String before is: %s\n", s);
        int x = rand() % 3 + 1;
        len -= x;
        if(len < 0)
            len = 0;
        s[len] = 0;
        printf("String after removing the last %d characters is: %s\n", x, s);

        if(0 != (k = write(b2a, &len, sizeof(int)))) {
            if(-1 == k) {
                error(0, errno, "Error sending string length %d", len);
                break;
            }
        }
        if(len == 0) {
            printf("Process B removed the last characters of the string\n");
            break;
        }
        if(0 != (k = write(b2a, s, sizeof(char) * len))){
            if(-1 == k) {
                error(0, errno, "Error sending string %s", s);
                break;
            }
        }
    } while(0 < (len = strlen(s)));
    free(s);
    close(a2b);
    close(b2a);
    return 0;
}
