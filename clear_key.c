#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("kateryna_vasiuk_335a.txt", 'R');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(key, 0, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    printf("Ключ IPC очищено.\n");

    return 0;
}
