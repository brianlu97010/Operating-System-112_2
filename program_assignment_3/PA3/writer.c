#include <lib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sem.c"

int main() {
    key_t key = 9876;
    int shmid;
    void **shm;
    if ((shmid = shmget(key, 50, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (void **) -1) {
        perror("shmat");
        exit(1);
    }

    int *buffer;
    key_t key2 = 9875;
    int shmid2;
    if ((shmid2 = shmget(key2, sizeof(int), 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((buffer = shmat(shmid2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    int *rd_count;
    key_t key3 = 9874;
    int shmid3;
    if ((shmid3 = shmget(key3, sizeof(int), 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((rd_count = shmat(shmid3, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    semaphore sem_m, sem_w;
    psem_init(&sem_m, 1, 3, 9877, 0);
    psem_init(&sem_w, 1, 3, 9878, 0);

    printf("Process %d launching\n", getpid());

    int input;
    while (printf("Enter a number: "), scanf("%d", &input) != EOF) {
        sem_wait(&sem_w, shm[1]);  // Wait until writing is allowed

        *buffer = input;
        printf("Process %d: wrote %d to the mailbox\n", getpid(), input);

        sem_post(&sem_w, shm[1]);  // Release the writing lock
        sleep(1);  // Add a small delay to simulate processing
    }

    return 0;
}

