/* CS 347 -- Mini Shell!
 * Original author Phil Nelson 2000
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include "argparse.h"
#include "builtin.h"

/* PROTOTYPES */

void processline(char *line);
ssize_t getinput(char **line, size_t *size);

/* main
 * This function is the main entry point to the program.  This is essentially
 * the primary read-eval-print loop of the command interpreter.
 */

int main()
{
  //Read in first command
  char **line = malloc(sizeof(char) * 100); //testers to get it to compile
  size_t *size = malloc(sizeof(char) * 100);
  do
  {
    printf("myshell >");
    getinput(line, size); //Call getinput to start the shell
    processline(*line);
  } while (1);

  return EXIT_SUCCESS;
}

/* getinput
* line     A pointer to a char* that points at a buffer of size *size or NULL.
* size     The size of the buffer *line or 0 if *line is NULL.
* returns  The length of the string stored in *line.
*
* This function prompts the user for input.  If the input fits in the buffer
* pointed to by *line, the input is placed in *line.  However, if there is not
* enough room in *line, *line is freed and a new buffer of adequate space is
* allocated.  The number of bytes allocated is stored in *size.
*/
ssize_t getinput(char **line, size_t *size)
{
  assert(line != NULL && size != NULL);

  errno = 0;
  //print the prompt e.g. %myshell%
  char **newLine = malloc(sizeof(char) * 10);
  ssize_t len = getline(newLine, size, stdin); //read input line from user, stores it in line        

  //write your codemicro
  if (len <= *size)
  { //Check if user input fits in the buffer

    *line = *newLine;
  }
  else
  {
    printf("Were in the malloc");
    //free and allocate if no room
    free(*line);
    line = malloc(len * sizeof(char)); //allocates len# of bytes
  }

  return len;
}

/* processline
 * The parameter line is interpreted as a command name.  This function creates a
 * new process that executes that command.
 * Note the three cases of the switch: fork failed, fork succeeded and this is
 * the child, fork succeeded and this is the parent (see fork(2)).
 * processline only forks when the line is not empty, and the line is not trying to run a built in command
 */
void processline(char *line)
{
  /*check whether line is empty*/
  if (line <= 0)
    return;

  pid_t cpid;
  int status;
  int argCount;
  char **arguments = argparse(line, &argCount);

  /*check whether arguments are builtin commands
   *fork, and execute the commands
   */
  if (!builtIn(arguments, argCount))
  {
    //Given cmd not buildin, therefore fork
    cpid = fork();
  }

  //if fork succeeded and this is child
  if (cpid == 0)
  {
    execvp(line, arguments);
  }
  else if (cpid < 0)
  { //if fork failed
    printf("%s", "Fork failed, exiting");
    exit(0);
  }
  else
  {             //if fork succeeded and this is parent
    wait(NULL); //wait for this parent's child to finish
  }
}
