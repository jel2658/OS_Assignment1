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

int main() {
    int shm_fd = shm_open("/queue", O_RDWR, 0666);
    int* q2 = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t* produce = sem_open("produce", O_CREAT, 0666, 0);
    sem_t* check = sem_open("ready", O_CREAT, 0666, 2);
    sem_t* locker = sem_open("locker", O_CREAT, 0666, 1);

    printf("It's consumption time (not the disease).");

    for (int i = 0; i < 50; i++) {
        sem_wait(produce);

        sleep(5); // wait 5 seconds

        sem_wait(locker);
        (*q2)--;
        sem_post(locker);

        printf("Yum!"); // Item has been consumed

        sem_post(check);
    }

    sem_close(produce);
    sem_close(check);
    sem_close(locker);

    sem_unlink("produce");
    sem_unlink("ready");
    sem_unlink("locker");

    munmap(q2, sizeof(int));
    close(shm_fd);
    shm_unlink("/queue");

    printf("Consumer done.");
    return 0;
}