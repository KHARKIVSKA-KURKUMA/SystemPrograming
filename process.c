#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("We use: %s <file_name>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r+");

    if (file == NULL) {
        perror("Error opening file");
        return 2;
    }


    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    char *buffer = (char *)malloc(fileSize + 1);
    fseek(file, 0, SEEK_SET);
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    
  for (int i = 0; i < fileSize; i++) {
    if (buffer[i] == 'a') {
      
        buffer[i] = 'A';
   
        memmove(buffer + i + 1, buffer + i, fileSize - i);
        buffer[i + 1] = 'o';
        fileSize += 1; // Збільшуємо розмір буфера на 1
        i++; // Перескакуємо через вставлену "о"
    }
}

    
    fseek(file, 0, SEEK_SET);

   
    char *studentInfo = "Student: Vasiuk Kateryna\nGroup: 335а\n";
    int studentInfoLength = strlen(studentInfo);
    fwrite(studentInfo, 1, studentInfoLength, file);

    
    fwrite(buffer, 1, fileSize, file);


    fclose(file);
    free(buffer);

    printf("File processed successfully\n");

    return 0;
}
