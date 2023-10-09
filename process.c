#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


int containsSignature(const char *source, const char *signature) {
    return strstr(source, signature) != NULL;
}


int readSignatureFromFile(const char *filename, char *signature, int max_length) {
    FILE *file = fopen(filename, "r");
    if (file) {
        if (fgets(signature, max_length, file)) {
            
            char *newline = strchr(signature, '\n');
            if (newline) {
                *newline = '\0';
            }
            fclose(file);
            return 1; 
        }
        fclose(file);
    }
    return 0; 
}

void scanDirectory(const char *path, const char *signature) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR) {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                    char subpath[512];
                    snprintf(subpath, sizeof(subpath), "%s/%s", path, entry->d_name);
                    scanDirectory(subpath, signature);
                }
            } else {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
                FILE *file = fopen(filepath, "r");
                if (file) {
                    char line[512]; 
                    while (fgets(line, sizeof(line), file)) {
                        if (containsSignature(line, signature)) {
                            printf("Знайдено файл з сигнатурою в %s\n", filepath);
                            break; 
                        }
                    }
                    fclose(file);
                }
            }
        }
        closedir(dir);
    }
}

int main() {
    const char *path = "/home/ksvasiuk";
    const char *signatureFilename = "signature.txt"; 

    char signature[512];
    if (readSignatureFromFile(signatureFilename, signature, sizeof(signature))) {
        scanDirectory(path, signature);
    } else {
        printf("Помилка: не вдалося прочитати сигнатуру з файлу %s\n", signatureFilename);
    }

    return 0;
}

