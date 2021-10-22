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

int main() { // Much code taken from lectures by the professor.
    int queue = shm_open("/queue", O_RDWR | O_CREAT, 0666);
    ftruncate(queue, sizeof(int));

    int* q2 = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, queue, 0);

    sem_t* produce = sem_open("produce", O_CREAT, 0666, 0);
    sem_t* check = sem_open("ready", O_CREAT, 0666, 2);
    sem_t* locker = sem_open("locker", O_CREAT, 0666, 1);

    printf("Production time!");

    for (int i = 0; i < 50; i++) { // Produce 50 times
        sem_wait(check);

        sleep(5); // Wait five seconds or less (signal)

        sem_wait(locker);
        (*q2) += 1;
        sem_post(locker);

        printf("Produced.");

        sem_post(produce);
    }

    sem_close(produce);
    sem_close(check);
    sem_close(locker);

    sem_unlink("produce");
    sem_unlink("ready");
    sem_unlink("locker");

    munmap(q2, sizeof(int));
    close(queue);
    shm_unlink("/queue");

    printf("Producer done.");
    return 0;
}