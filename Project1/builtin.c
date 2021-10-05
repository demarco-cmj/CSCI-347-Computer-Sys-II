#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "builtin.h"
#include <string.h>
#include <dirent.h>

//Prototypes
static void exitProgram(char **args, int argcp);
static void cd(char **args, int argpcp);
static void pwd(char **args, int argcp);
static void help(char **args, int argcp);
//static void ls();

/* builtIn
 ** built in checks each built in command the given command, if the given command
 * matches one of the built in commands, that command is called and builtin returns 1.
 *If none of the built in commands match the wanted command, builtin returns 0;
*/
int builtIn(char **args, int argcp)
{
  if (strcmp(args[0], "pwd") == 0)
  {
    pwd(args, argcp);
    return 1;
  }

  else if (strcmp(args[0], "exit") == 0)
  {
    exitProgram(args, argcp);
    return 1;
  }

  else if (strcmp(args[0], "cd") == 0)
  {
    cd(args, argcp);
    return 1;
  }
  else if (strcmp(args[0], "help") == 0)
  {
    help(args, argcp);
    return 1;
  }

  printf("Command not supported by the shell use help to get something new!.\n");
  return 0;
}
/*
//Similar to the built in we compare the second value with one of our operations 
//If it doesnt work then we give them a list of our operations
*/
static void help(char **args, int argcp)
{
  //List of available builtin commands
  if (argcp > 1)
  {
    if (strcmp(args[1], "pwd") == 0)
      printf("This command stands for \"path of working directory\", and prints such to terminal.\n");

    else if (strcmp(args[1], "exit") == 0)
      printf("This command closes the shell.\n");

    else if (strcmp(args[1], "cd") == 0)
      printf("This command stands for \"change directory\"\n");

    else if (strcmp(args[1], "help") == 0)
      printf("Well.... you made it here! So good job!\n");

    else
      printf("Your second argument isnt one we have! try \"help pwd\"\n");
  }
  else
    printf("Help with Connor and Myles' Shell.\nHere is a list of commands: help, exit, cd, pwd \ntype help again with a specified function name for more info (eg. help pwd): \n");
}
/*
/If using exit with a value argcp of 1 we just exit with 3
*/
static void exitProgram(char **args, int argcp)
{
  if (argcp == 1)
    exit(3);

  else
    exit((size_t)args[1]);
}
/*
*Initialize a char array and use getcwd to then print out the directory
*/
static void pwd(char **args, int argcp)
{
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));
  printf("%s\n", cwd);
}
/*
*If the argcp value is greater than 1 we go to that directory. 
*Prior to that we recieve the current working directory
*/
static void cd(char **args, int argcp)
{
  char curCD[1024];
  char *newCD = getcwd(curCD, sizeof(curCD));

  if (argcp > 1)
  {
    chdir(args[1]);
    setenv("PWD", newCD, 1);
  }
}
/*
* Partially implemented ls function
* This section was scrapped and we would like help to be graded 
*/
//static void ls()
///{
// DIR *d;
// struct dirent *dir;
// d = opendir(".");
// if (d) {
//   while ((dir = readdir(d)) != NULL)
//     printf("%s\n", dir->d_name);

//   //closedir(d);
// }
// free(dir);
//}