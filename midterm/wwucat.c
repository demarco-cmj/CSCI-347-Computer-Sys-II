//Connor DeMarco
//CSCI 347
//2/16/21

#include <fcntl.h>
#include <unistd.h>              
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BUF_SIZE 32               /* Size of buffer */

#define FILE_NAME_LEN 200         /* Maximum length of file name */

int main(int argc, char *argv[]){
    //Local Variables
    char temp;
    
    //Expected one file name error
    if(argc < 1){
        printf("%s", "Expecting 1 filename\n");
        return 0;
    }

    for(int i = 1; i < argc; i++){
        //Open next command arg as file
        char* file = argv[i];
        int pFile = open(file, O_RDONLY);

        //Read until EOF
        if(read(pFile, &temp, 1) == 1){
            //Print to standard output
            if(errno == 0){ //check errno to see if problem occured while reading
                if(printf("%c", temp) < 0){ //check return value of printf
                    printf("%s", "Error while writing to standard output");
                    break;
                }


                while(read(pFile, &temp, 1) == 1){
                    printf("%c", temp);
                }
            }else{
                printf("%s", "Error while reading the file\n");
            }

        }else{ //Error opening file
            printf("%s", "Error while opening the file for reading\n");
        }
        close(pFile);
    }
    return 0;
}