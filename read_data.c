#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


struct SharedData {
    char student_name[50];
    char student_group[10];
    int student_age;
   
};

int main() {
    key_t key = ftok("kateryna_vasiuk_335a.txt", 'R');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    
    int shmid = shmget(key, sizeof(struct SharedData), 0666);
    if (shmid == -1) {
        perror("shmget");
        printf("Сегмент спільної пам'яті не існує або ключ відсутній.\n");
        exit(EXIT_FAILURE);
    }

    struct SharedData *data = (struct SharedData *)shmat(shmid, (void *)0, 0);
    if (data == (struct SharedData *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

   
    printf("ПІБ студента: %s\n", data->student_name);
    printf("Номер групи студента: %s\n", data->student_group);
    printf("Bік студента: %d\n", data->student_age);

    shmdt((void *)data);

    return 0;
}
