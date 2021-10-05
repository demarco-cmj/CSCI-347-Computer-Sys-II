//Connor DeMarco
//CSCI 347
//1/26/21

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv)
{

    char outputFile[128];
    char* command = argv[1];
    char* file = argv[2];


    if (strcmp(argv[1], "-e") == 0)
    {
        int pFile = open(file, O_RDONLY);
        strcpy(outputFile, file);
        strtok(outputFile, ".");
        strcat(outputFile, "_enc.txt");

        char *outfile = "_enc.txt";
        int fd = creat(outfile, O_WRONLY);


        //Local Variables
        int i = 0;

        while(read(pFile, &outputFile[i], 1) == 1){
            //Adjust the char's ascii values
            outputFile[i] += 100;

            //Write to file
            write(fd, &outputFile[i], 1);
            i++;
        }
        return 0;
    }

    if (strcmp(argv[1], "-d") == 0)
    {
        int pFile = open(file, O_RDONLY);
        strcpy(outputFile, file);
        strtok(outputFile, ".");
        strcat(outputFile, "_enc.txt");

        char *outfile = "_dec.txt";
        int fd = creat(outfile, O_WRONLY);


        //Local Variables
        int i = 0;

        while(read(pFile, &outputFile[i], 1) == 1){
            //Adjust the char's ascii values
            outputFile[i] -= 100;

            //Write to file
            write(fd, &outputFile[i], 1);
            i++;
        }
        return 0;
    }

}

