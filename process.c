#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <time.h>

#define MAX_PATH_LENGTH 512
#define MAX_SIGNATURE_LENGTH 512

volatile int program_should_exit = 0;

void handle_interrupt(int signum)
{
    printf("\nПрограма завершилася за допомогою Ctrl+C.\n");
    printf("Час завершення програми: %s", asctime(localtime(&(time_t){time(NULL)})));
    printf("Student: Vasiuk Kateryna\n");
    program_should_exit = 1;
}

int containsSignature(const char *source, const char *signature, size_t sourceLength, size_t signatureLength)
{
    char *result = memmem(source, sourceLength, signature, signatureLength);
    return result != NULL;
}

int readSignatureFromFile(const char *filename, char *signature, size_t max_length)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        size_t bytesRead = fread(signature, 1, max_length - 1, file);
        if (bytesRead > 0)
        {
            signature[bytesRead] = '\0';
            fclose(file);
            return 1;
        }
        fclose(file);
    }
    return 0;
}

void scanDirectory(const char *path, const char *signature)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) != NULL)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    char subpath[MAX_PATH_LENGTH];
                    snprintf(subpath, sizeof(subpath), "%s/%s", path, entry->d_name);
                    scanDirectory(subpath, signature);
                }
            }
            else
            {
                char filepath[MAX_PATH_LENGTH];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
                FILE *file = fopen(filepath, "r");
                if (file)
                {
                    fseek(file, 0, SEEK_END);
                    size_t fileLength = ftell(file);
                    fseek(file, 0, SEEK_SET);

                    char *fileContents = (char *)malloc(fileLength);
                    if (fileContents)
                    {
                        fread(fileContents, 1, fileLength, file);

                        if (containsSignature(fileContents, signature, fileLength, strlen(signature)))
                        {
                            printf("Знайдено файл з сигнатурою в %s\n", filepath);
                        }

                        free(fileContents);
                    }

                    fclose(file);
                }
            }
        }
        closedir(dir);
    }
}

int main()
{
    signal(SIGINT, handle_interrupt);

    const char *path = "/home/vasiuk";
    const char *signatureFilename = "signature.txt";

    char signature[MAX_SIGNATURE_LENGTH];
    if (readSignatureFromFile(signatureFilename, signature, sizeof(signature)))
    {
        while (!program_should_exit) {
            scanDirectory(path, signature);
        }
    }
    else
    {
        printf("Помилка: не вдалося прочитати сигнатуру з файлу %s\n", signatureFilename);
    }

    return 0;
}
