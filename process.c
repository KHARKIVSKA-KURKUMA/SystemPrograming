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

    
    char buffer[21];  
    size_t bytesRead = fread(buffer, 1, 20, inputFile);
    buffer[bytesRead] = '\0';

   
    fwrite(buffer, 1, bytesRead, outputFile);

    char *studentInfo = "Vasiuk Kateryna 335a";
    int studentInfoLength = strlen(studentInfo);

   
    fwrite(studentInfo, 1, studentInfoLength, outputFile);

   
    char fileBuffer[1024];
    while ((bytesRead = fread(fileBuffer, 1, sizeof(fileBuffer), inputFile)) > 0) {
        fwrite(fileBuffer, 1, bytesRead, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File processed successfully\n");

    return 0;
}