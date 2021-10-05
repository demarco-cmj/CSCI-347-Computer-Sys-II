//Connor DeMarco
//CSCI 347
//1/29/21

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]){
    mode_t file_perm;          /* File permissions */
    struct stat file_details;  /* Detailed file info */

    //Set file path
    stat(argv[1], &file_details);

    //Report file Type
    if(S_ISDIR(file_details.st_mode)){
        printf("%s", "File type: Directory\n");
    }
    else if(S_ISREG(file_details.st_mode)){
        printf("%s", "File type: Regular\n");
    }
    

    //Time of last modification

    printf("%s", "Time of last access: ");
    char time[50]; //Save space for array to then print
    strftime(time, 50, "%Y-%m-%d %H:%M:%S", localtime(&(file_details.st_atime))); //use st_atime with localtime
    printf ("%s\n", time);
    

    //Check and print file RWX permissions
    printf("File Permissions:\n");

    printf("%s", "User: "); //USER PERMISSIONS
    if(file_details.st_mode & S_IRUSR)              //&'s permission bits of file_details with the current argument
        printf("%s", "Readable, ");
    else
        printf("%s", "Not readable, ");     
    if(file_details.st_mode & S_IWUSR)
        printf("%s", "Writable, ");
    else
        printf("%s", "Not writable, ");  
    if(file_details.st_mode & S_IXUSR)
        printf("%s", "Executable\n");
    else
        printf("%s", "Not executable\n");

    printf("%s", "Group: "); //GROUP PERMISSIONS
    if(file_details.st_mode & S_IRGRP)
        printf("%s", "Readable, ");
    else
        printf("%s", "Not readable, ");     
    if(file_details.st_mode & S_IWGRP)
        printf("%s", "Writable, ");
    else
        printf("%s", "Not writable, ");  
    if(file_details.st_mode & S_IXGRP)
        printf("%s", "Executable\n");
    else
        printf("%s", "Not executable\n");

    printf("%s", "Other: "); //OTHER PERMISSIONS
    if(file_details.st_mode & S_IROTH)
        printf("%s", "Readable, ");
    else
        printf("%s", "Not readable, ");     
    if(file_details.st_mode & S_IWOTH)
        printf("%s", "Writable, ");
    else
        printf("%s", "Not writable, ");  
    if(file_details.st_mode & S_IXOTH)
        printf("%s", "Executable\n");
    else
        printf("%s", "Not executable\n");  


    //Return
    return 0;

}
