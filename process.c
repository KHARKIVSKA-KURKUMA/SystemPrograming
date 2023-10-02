#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int inputFile = open(argv[1], O_RDONLY);
    if (inputFile == -1)
    {
        perror("Error opening input file");
        return 2;
    }

    int outputFile = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outputFile == -1)
    {
        perror("Error opening output file");
        close(inputFile);
        return 3;
    }

    int character;
    int count = 0;

    while (read(inputFile, &character, 1) == 1)
    {
        if (character == 'a')
        {
            char *replacement = "Ao";
            write(outputFile, replacement, strlen(replacement));
            count += 2;
        }
        else
        {
            write(outputFile, &character, 1);
            count++;
        }

        if (count == 20)
        {
            char *studentInfo = "Vasiuk Kateryna 335a";
            write(outputFile, studentInfo, strlen(studentInfo));
        }
    }

    close(inputFile);
    close(outputFile);

    printf("File processed successfully\n");

    return 0;
}
