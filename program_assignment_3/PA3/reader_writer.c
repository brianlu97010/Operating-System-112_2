#include <lib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#include "sem.c"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage:\n\t$ %s capacity\n", argv[0]);
        return 0;
    }

    int capacity = atoi(argv[1]);

    // Open the log files
    FILE *fd;
    fd = fopen("semLogfile", "w+");
    fprintf(fd, "");
    fclose(fd);

    fd = fopen("rwLogfile", "w+");
    fprintf(fd, "");
    fclose(fd);

    // Shared semaphores
    key_t key = 9876;
    int shmid;
    void **shm;
    if ((shmid = shmget(key, 50, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (void **) -1) {
        perror("shmat");
        exit(1);
    }

    // Shared buffer for mailbox
    int *buffer;
    int shmid2;
    key_t key2 = 9875;
    if ((shmid2 = shmget(key2, sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((buffer = shmat(shmid2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Initialize reader count
    int *rd_count;
    key_t key3 = 9874;
    int shmid3;
    if ((shmid3 = shmget(key3, sizeof(int), IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((rd_count = shmat(shmid3, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    *rd_count = 0;

    // Mutex and writing semaphores
    semaphore sem_m, sem_w;
    shm[0] = psem_init(&sem_m, 1, 3, 9877, 1);
    shm[1] = psem_init(&sem_w, 1, 3, 9878, 1);

    // Launch writer process
    int pid = fork();
    if (pid == 0) {
        execlp("./writer", "writer", (char *)NULL);
    }

    // Launch reader processes
    for (int i = 0; i < 2; i++) {
        pid = fork();
        if (pid == 0) {
            execlp("./reader", "reader", (char *)NULL);
        }
    }

    // Wait for all child processes to complete
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Destroy semaphores
    psem_destroy(&sem_m);
    psem_destroy(&sem_w);
    m.m1_p1 = shm[0];
    _syscall(PM_PROC_NR, PSEM_DESTROY, &m);
    m.m1_p1 = shm[1];
    _syscall(PM_PROC_NR, PSEM_DESTROY, &m);

    // Delete shared memory segments
    shmdt(shm);
    shmctl(shmid, IPC_RMID, 0);
    shmdt(buffer);
    shmctl(shmid2, IPC_RMID, 0);
    shmdt(rd_count);
    shmctl(shmid3, IPC_RMID, 0);

    return 0;
}

