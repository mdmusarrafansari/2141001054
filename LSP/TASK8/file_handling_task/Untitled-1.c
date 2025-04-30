#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key = 1234;  // Key for shared memory segment
    int shmid;
    char *shm_ptr;

    // Create shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    shm_ptr = (char*) shmat(shmid, NULL, 0);
    if (shm_ptr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write a message to shared memory
    printf("Writer: Enter a message to store in shared memory: ");
    fgets(shm_ptr, SHM_SIZE, stdin);  // Write message to shared memory

    // Detach the shared memory segment
    shmdt(shm_ptr);

    printf("Writer: Message written to shared memory.\n");
    return 0;
}
