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
#include <errno.h>

void display(char *prog, char *bytes, int n);

int main() {    // Decent portion of code borrowed from github so that I could make a working program.
    const char *name = "/queue"; // The name of the file that we open to share memory
    const int FILESIZ = 5000;   // The size of the file that will be shared

    int shm_fd = shm_open(name, O_RDWR, 0666);  // Opens up the shared file.
    if (shm_fd == -1) { // Checks to make sure the file has actually been opened
        printf("Failed to shm_open.");
        exit(1);
    }

    //int* q2 = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    char *base_address = mmap(0, FILESIZ, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); // Open up the shared memory address?
    if (base_address == MAP_FAILED) {   // Checks to make sure the address was opened.
        printf("Failed to map.");
        exit(1);
    }

    display("Consumer", base_address, 64); // The helper function, display... outputs what's in the shared memory
    printf("%s", base_address);

    if (munmap(base_address, FILESIZ) == -1) {  // Unmap the shared memory address and check to make sure it's unmapped.
        printf("Failed to unmap.");
        exit(1);
    }

    if (close(shm_fd) == -1) {  // Close the shared memory address, then check to make sure it's closed.
        printf("Failed to close consumer.");
        exit(1);
    }

    if (shm_unlink(name) == -1) {   // Unlink the shared memory and check that it is.
        printf("Consumer failed to unlink.");
        exit(1);
    }

    /*sem_t* produce = sem_open("produce", O_CREAT, 0666, 0); // This code made me confused and didn't work, but I'll keep it for documentation.
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

    printf("Consumer done.");*/
    return 0;
}

void display(char *prog, char *bytes, int n) { // Print that we are now in the display() function, then print the shared array in the memory address.
    printf("Display: %p", prog);

    for (int i = 0; i < n; ++i) {
        printf("%02x%c", bytes[i], ((i+1)%16) ? ' ' : '\n');
    }

    printf("\n");
}
