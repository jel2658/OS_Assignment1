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

void display(char *prog, char *bytes, int n);   // Taken from github to try and replicate a successful posix example.
                                                //Helper function that will output the shared array.

int main() { // Much code taken from lectures by the professor, as well as the github mentioned in the README.
    const char *name = "/queue";    //Name of file to share.
    const int FILESIZ = 5000;   //Size of file shared.

    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); //Open shared file.
    if (shm_fd == -1) {
        printf("Producer failed to share memory.");
        exit(1);
    }

    ftruncate(shm_fd, FILESIZ); //Make sure the file size is correct.

    char *base_address = mmap(0, FILESIZ, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (base_address == MAP_FAILED) {
        printf("Producer failed to map memory segment.");
        exit(1);
    }

    char *pointer = base_address;

    display("Producer.", base_address, 64);
    for (int i = 0; i < 64; i++) {
        pointer += i;
    }
    display("Producer.", base_address, 64);

    if (munmap(base_address, FILESIZ) == -1) {
        printf("Producer failed to unmap.");
        exit(1);
    }

    if (close(shm_fd) == -1) {
        printf("Producer failed to close share memory segment.");
        exit(1);
    }

    /*int queue = shm_open("/queue", O_RDWR | O_CREAT, 0666);
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

    printf("Producer done.");*/
    return 0;
}

void display(char *prog, char *bytes, int n) {
    printf("Displaying %s", prog);
    for (int i = 0; i < n; i++) {
        printf("%02x%c", bytes[i], ((i+1)%16) ? ' ' : '\n');
    }
    printf("\n");
}