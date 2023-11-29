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

    int shmid = shmget(key, sizeof(struct SharedData), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    struct SharedData *data = (struct SharedData *)shmat(shmid, (void *)0, 0);
    if (data == (struct SharedData *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Введіть ПІБ студента: ");
    fgets(data->student_name, sizeof(data->student_name), stdin);
    data->student_name[strcspn(data->student_name, "\n")] = '\0'; 
    
    printf("Введіть номер групи студента: ");
    fgets(data->student_group, sizeof(data->student_group), stdin);
    data->student_group[strcspn(data->student_group, "\n")] = '\0'; 
    
    printf("Введіть вік студента: ");
    scanf("%d", &data->student_age);

    printf("Дані записано в спільну пам'ять.\n");
    shmdt((void *)data);

    return 0;
}
