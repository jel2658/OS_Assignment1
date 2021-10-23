/*#include <sys/mman.h>  DON'T USE THIS FILE
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>

//#define SHMSIZE 1024

void display(char *prog, char *bytes, int n);   // Taken from github to try and replicate a successful posix example.
                                                //Helper function that will output the shared array.

int main(void) {
    /*key_t key;
    int shmid;
    int cnt;
    int infinite_loop = 1;
    char *shm, *s;
    char line[BUFSIZ];
    FILE * digits;

    digits = fopen("digits.out", "w");

    key = getuid();

    shmid = shmget(key, SHMSIZE, 0666);

    if (shmid < 0) {
        perror("failed shmget, created no shared segment");
        exit(EXIT_FAILURE);
    }

    shm = shmat(shmid, NULL, 0);*/
//}*/