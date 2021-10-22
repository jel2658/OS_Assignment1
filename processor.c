#include <sys/mman.h>
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

#define SHMSIZE 1024

int main(void) {
    key_t key;
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

    shm = shmat(shmid, NULL, 0);
}