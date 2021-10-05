#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "argparse.h"
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define FALSE (0)
#define TRUE (1)

static int argCount(char *line);

/*
* argCount is a helper function that takes in a String and returns the number of "words" in the string assuming that whitespace is the only possible delimeter.
*/
static int argCount(char *line)
{
  //I check if theres a space then after that I dont increment the words until there is not a space.
  int tot_words = 0;
  int i = 0;
  while (*line)
  {
    if (isspace(*line))
      i = 0;

    else if (i == 0)
    {
      i = 1;
      tot_words++;
    }
    line++;
  }
  return tot_words;
}

/*
*
* Argparse takes in a String and returns an array of strings from the input.
* The arguments in the String are broken up by whitespaces in the string.
* The count of how many arguments there are is saved in the argcp pointer
*/
char **argparse(char *line, int *argcp)
{
  *argcp = argCount(line);

  char **arr_strings = malloc((size_t)*argcp);

  int j = 0;
  for (int i = 0; i < *argcp; i++)
  { //for each word found
    char *tempStr = malloc(sizeof(char) * 10);
    while (!isspace(*line))
    {
      tempStr[j] = *line;
      j++;
      line++;
    }

    tempStr[j] = '\0';
    j = 0;
    line++;
    arr_strings[i] = tempStr;
  }
  return arr_strings;
}