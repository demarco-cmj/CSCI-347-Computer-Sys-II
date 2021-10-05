//Connor DeMarco
//1/22/21
//CSCI 347

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define FALSE (0)
#define TRUE  (1)

int main(int argc, char** argv) {
	int tot_chars = 0 ;	/* total characters */
	int tot_lines = 0 ;	/* total lines */
	int tot_words = 0 ;	/* total words */


	char temp;
	char previous;
	
	do{
		temp = getchar(); //Gets next char from file provided in command prompt
		tot_chars++;

		if(temp == ' ' && previous != ' ' && previous != '\n'){ //IF white space and previous was part of a word, ADD WORD
			tot_words++;
		}	
		else if(temp == '\n' && previous != ' ' && previous != '\n'){ //IF temp is a new line and previous was part of a word, ADD WORD & LINE
			tot_lines++;
			tot_words++;
		}
		else if(temp == '\n' && previous == '\n'){	//IF temp is new line and previous is new line, just ADD LINE
			tot_lines++;
		}

		previous = temp; //Set previous = temp for the next loop.
	}while(temp != EOF);
	tot_chars--; //Decrement chars for EOF char.
	
	printf("%i", tot_lines); printf("%s", " ");
	printf("%i", tot_words); printf("%s", " ");
	printf("%i", tot_chars); printf("%s", "\n");

	return 0 ;
}

