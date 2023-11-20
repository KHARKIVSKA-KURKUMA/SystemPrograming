#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_DATA_SIZE 1000

typedef struct {
    char data[MAX_DATA_SIZE];
    void (*sort_func)(char *data, int size); 
} ThreadData;

// Функція сортування бульбашкою
void bubbleSort(char *data, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                char temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }
}

// Функція сортування злиттям
void merge(char *data, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    char L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (j = 0; j < n2; j++)
        R[j] = data[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

// Функція сортування злиттям (рекурсивний виклик)
void mergeSortRecursive(char *data, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortRecursive(data, left, middle);
        mergeSortRecursive(data, middle + 1, right);
        merge(data, left, middle, right);
    }
}

// Функція сортування злиттям (обгортка для використання в потоці)
void mergeSort(char *data, int size) {
    mergeSortRecursive(data, 0, size - 1);
}

// Функція, яка виконує сортування в потоці
void *sortInThread(void *arg) {
    ThreadData *threadData = (ThreadData *)arg;
    threadData->sort_func(threadData->data, strlen(threadData->data));
    pthread_exit(NULL);
}

int main() {
    char data[MAX_DATA_SIZE] = "Vasiuk Kateryna, 335а, 11.01.2003";

    ThreadData threadData;
    strcpy(threadData.data, data);

    threadData.sort_func = bubbleSort;
    pthread_t bubbleSortThread;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    pthread_create(&bubbleSortThread, NULL, sortInThread, (void *)&threadData);

    pthread_join(bubbleSortThread, NULL);
    gettimeofday(&end, NULL);
    printf("Bubble Sort Time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    threadData.sort_func = mergeSort;
    pthread_t mergeSortThread;
    gettimeofday(&start, NULL);
    pthread_create(&mergeSortThread, NULL, sortInThread, (void *)&threadData);

    pthread_join(mergeSortThread, NULL);
    gettimeofday(&end, NULL);
    printf("Merge Sort Time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    bubbleSort(data, strlen(data));
    gettimeofday(&end, NULL);
    printf("Bubble Sort Without Threads Time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    gettimeofday(&start, NULL);
    mergeSort(data, strlen(data));
    gettimeofday(&end, NULL);
    printf("Merge Sort Without Threads Time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec);

    return 0;
}
