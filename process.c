#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 2;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 3;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    fread(buffer, 1, fileSize, inputFile);
    buffer[fileSize] = '\0';

    for (int i = 0; i < fileSize; i++) {
        if (buffer[i] == 'a') {
            buffer[i] = 'A';
            memmove(buffer + i + 1, buffer + i, fileSize - i);
            buffer[i + 1] = 'o';
            fileSize += 1; 
            i++; 
        }
    }

    char *studentInfo = "Student: Vasiuk Kateryna\nGroup: 335a\n";
    int studentInfoLength = strlen(studentInfo);

    fwrite(studentInfo, 1, studentInfoLength, outputFile);
    fwrite(buffer, 1, fileSize, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    free(buffer);

    printf("File processed successfully\n");

    return 0;
}
