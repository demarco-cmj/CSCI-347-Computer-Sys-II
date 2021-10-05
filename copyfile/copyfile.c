//Connor DeMarco
//CSCI 347
//2/3/21


#include <stdio.h>                /* Standard library for file operations */
#include <string.h>               /* String functions (strcat) */
#include <stdbool.h>
#define BUF_SIZE 32               /* Size of buffer */


 
int main(int argc, char *argv[])
{
       FILE * file_to_read;        // File to be copied
       FILE * file_to_write;       // Copy of the file
       
       char buf[BUF_SIZE];        // Buffer to hold characters read 
       size_t n, m;               // Number of records to be read/written


       if(argv[1] != NULL && argv[2] != NULL) {  //Both in and out file provided
              //Open files
              file_to_read = fopen(argv[1], "rb");
              file_to_write = fopen(argv[2], "wb");

              //Copy contents
              do {
                     n = fread(buf, 1, sizeof buf, file_to_read);
                     if (n) m = fwrite(buf, 1, n, file_to_write);
                     else   m = 0;
              } while ((n > 0) && (n == m));

              //Close Files
              fclose(file_to_write);
              fclose(file_to_read);
       }
       else if(argv[1] != NULL && argv[2] == NULL) { //No output file
              //Open read file
              file_to_read = fopen(argv[1], "rb");

              //Create/open write file
              char fileName[50];
              strcpy(fileName, argv[1]);
              strcat(fileName, ".output");
              file_to_write = fopen(fileName, "wb");

              //Copy contents
              do {
                     n = fread(buf, 1, sizeof buf, file_to_read);
                     if (n) m = fwrite(buf, 1, n, file_to_write);
                     else   m = 0;
              } while ((n > 0) && (n == m));
              
              //Close Files
              fclose(file_to_write);
              fclose(file_to_read);
       }
       else { //Incorrect input
              printf("%s", "Incorrect input. Usage: \n ./copyfile <src_file_name> [<target_file_name>]");
       }      
       return 0;
}

