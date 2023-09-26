#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        perror("Error opening input file");
        return 2;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL)
    {
        perror("Error opening output file");
        fclose(inputFile);
        return 3;
    }

    int character;
    int count = 0;

    while ((character = fgetc(inputFile)) != EOF)
    {
        if (character == 'a')
        {

            fputs("Ao", outputFile);
            count += 2;
        }
        else
        {

            fputc(character, outputFile);
            count++;
        }

        if (count == 20)
        {
            char *studentInfo = "Vasiuk Kateryna 335a";
            fwrite(studentInfo, 1, strlen(studentInfo), outputFile);
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("File processed successfully\n");

    return 0;
}
