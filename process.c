#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <string.h>

/* ----------- a)	За допомогою низькорівневих функцій вводу-виводу ---------- */
void createLowLevelFile(const char *filename, off_t file_size)
{
    char buffer[4096];
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    for (off_t i = 0; i < file_size; i += sizeof(buffer))
    {
        write(fd, buffer, sizeof(buffer));
    }
    close(fd);
    gettimeofday(&end_time, NULL);
    long creation_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Час створення файлу (низькорівневий): %ld мікросекунд\n", creation_time);
}

/* ----- b)	За допомогою стандартних функцій для роботи з файлами мови С ---- */
void createStandardFile(const char *filename, off_t file_size)
{
    char buffer[4096];
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    FILE *file = fopen(filename, "wb");
    for (off_t i = 0; i < file_size; i += sizeof(buffer))
    {
        fwrite(buffer, 1, sizeof(buffer), file);
    }
    fclose(file);
    gettimeofday(&end_time, NULL);
    long creation_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Час створення файлу (стандартний): %ld мікросекунд\n", creation_time);
}

/* --------------------- c)	За допомогою функції mmap(). -------------------- */
void createMmapFile(const char *filename, off_t file_size)
{
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    ftruncate(fd, file_size);
    void *addr = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    memset(addr, 'A', file_size);
    gettimeofday(&end_time, NULL);
    long creation_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Час створення файлу (mmap): %ld мікросекунд\n", creation_time);
}

/* ----------- a)	За допомогою низькорівневих функцій вводу-виводу ---------- */
void copyLowLevelFile(const char *source_filename, const char *dest_filename)
{
    char buffer[4096];
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    int source_fd = open(source_filename, O_RDONLY);
    int dest_fd = open(dest_filename, O_WRONLY | O_CREAT, 0644);
    while (1)
    {
        ssize_t bytes_read = read(source_fd, buffer, sizeof(buffer));
        if (bytes_read <= 0)
            break;
        write(dest_fd, buffer, bytes_read);
    }
    close(source_fd);
    close(dest_fd);
    gettimeofday(&end_time, NULL);
    long copy_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Час копіювання файлу (низькорівневий): %ld мікросекунд\n", copy_time);
}

/* ----- b)	За допомогою стандартних функцій для роботи з файлами мови С ---- */
void copyStandardFile(const char *source_filename, const char *dest_filename)
{
    char buffer[4096];
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    FILE *source_file = fopen(source_filename, "rb");
    FILE *dest_file = fopen(dest_filename, "wb");
    while (1)
    {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), source_file);
        if (bytes_read == 0)
            break;
        fwrite(buffer, 1, bytes_read, dest_file);
    }
    fclose(source_file);
    fclose(dest_file);
    gettimeofday(&end_time, NULL);
    long copy_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Час копіювання файлу (стандартний): %ld мікросекунд\n", copy_time);
}

/* --------------------- c)	За допомогою функції mmap(). -------------------- */
void copyMmapFile(const char *source_filename, const char *dest_filename)
{
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    int source_fd = open(source_filename, O_RDONLY);
    if (source_fd == -1)
    {
        perror("open source file");
        return;
    }
    int dest_fd = open(dest_filename, O_WRONLY | O_CREAT, 0644);
    if (dest_fd == -1)
    {
        perror("open destination file");
        close(source_fd);
        return;
    }
    off_t source_size = lseek(source_fd, 0, SEEK_END);
    void *source_map = mmap(NULL, source_size, PROT_READ, MAP_PRIVATE, source_fd, 0);
    if (source_map == MAP_FAILED)
    {
        perror("mmap source file");
        close(source_fd);
        close(dest_fd);
        return;
    }
    if (write(dest_fd, source_map, source_size) == -1)
    {
        perror("write destination file");
    }
    munmap(source_map, source_size);
    close(source_fd);
    close(dest_fd);
    gettimeofday(&end_time, NULL);
    long copy_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("Час копіювання файлу (mmap): %ld мікросекунд\n", copy_time);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Використання: %s <операція> [інші аргументи]\n", argv[0]);
        return 1;
    }

    const char *operation = argv[1];

    if (strcmp(operation, "create_lowlevel") == 0)
    {
        if (argc != 4)
        {
            printf("Потрібно вказати ім'я файлу та розмір для операції 'create_lowlevel'.\n");
            return 1;
        }
        const char *filename = argv[2];
        off_t file_size = atoll(argv[3]);
        createLowLevelFile(filename, file_size);
    }
    else if (strcmp(operation, "create_standard") == 0)
    {
        if (argc != 4)
        {
            printf("Потрібно вказати ім'я файлу та розмір для операції 'create_standard'.\n");
            return 1;
        }
        const char *filename = argv[2];
        off_t file_size = atoll(argv[3]);
        createStandardFile(filename, file_size);
    }
    else if (strcmp(operation, "create_mmap") == 0)
    {
        if (argc != 4)
        {
            printf("Потрібно вказати ім'я файлу та розмір для операції 'create_mmap'.\n");
            return 1;
        }
        const char *filename = argv[2];
        off_t file_size = atoll(argv[3]);
        createMmapFile(filename, file_size);
    }
    else if (strcmp(operation, "copy_lowlevel") == 0)
    {
        if (argc != 4)
        {
            printf("Потрібно вказати ім'я вихідного та нового файлів для операції 'copy_lowlevel'.\n");
            return 1;
        }
        const char *source_filename = argv[2];
        const char *dest_filename = argv[3];
        copyLowLevelFile(source_filename, dest_filename);
    }
    else if (strcmp(operation, "copy_standard") == 0)
    {
        if (argc != 4)
        {
            printf("Потрібно вказати ім'я вихідного та нового файлів для операції 'copy_standard'.\n");
            return 1;
        }
        const char *source_filename = argv[2];
        const char *dest_filename = argv[3];
        copyStandardFile(source_filename, dest_filename);
    }
    else if (strcmp(operation, "copy_mmap") == 0)
    {
        if (argc != 4)
        {
            printf("Потрібно вказати ім'я вихідного та нового файлів для операції 'copy_mmap'.\n");
            return 1;
        }
        const char *source_filename = argv[2];
        const char *dest_filename = argv[3];
        copyMmapFile(source_filename, dest_filename);
    }
    else
    {
        printf("Невідома операція: %s\n", operation);
        return 1;
    }

    return 0;
}
