/*
 * Implementation of functions that find values in strings.
 *****
 * YOU MAY NOT USE ANY FUNCTIONS FROM <string.h>
 *****
 */

#include <stdlib.h>
#include <stdbool.h>

#include "find.h"

#define NOT_FOUND (-1)	// integer indicator for not found.

/*
 * Return the index of the first occurrence of <ch> in <string>,
 * or (-1) if the <ch> is not in <string>.
 */
int find_ch_index(char string[], char ch) {
	for(int i = 0; i < sizeof(string) - 1; i++){
		if(ch == string[i])
			return i;
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of <ch> in <string>,
 * or NULL if the <ch> is not in <string>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_ch_ptr(char *string, char ch) {
	while(*string){
		if(*string == ch)
			return string;
		string++;
	}
	return NULL;
}

/*
 * Return the index of the first occurrence of any character in <stop>
 * in the given <string>, or (-1) if the <string> contains no character
 * in <stop>.
 */
int find_any_index(char string[], char stop[]) {
	char temp;
	int index = 0;

	while(*string){
		temp = *string++;
		int j = 0;
		while(stop[j]){
			if(temp == stop[j])
				return index;
			j++;
		}
		index++;
	}
	return -1;
}

/*
 * Return a pointer to the first occurrence of any character in <stop>
 * in the given <string> or NULL if the <string> contains no characters
 * in <stop>.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_any_ptr(char *string, char* stop) {
	char* stopTemp = stop;

	while(*string){
		while(*stopTemp){
			if(*stopTemp++ == *string)
				return string;
		}
		*string++;
		stopTemp = stop;
	}
	return NULL;
}

/*
 * Return a pointer to the first character of the first occurrence of
 * <substr> in the given <string> or NULL if <substr> is not a substring
 * of <string>.
 * Note: An empty <substr> ("") matches *any* <string> at the <string>'s
 * start.
 *****
 * YOU MAY *NOT* USE INTEGERS OR ARRAY INDEXING.
 *****
 */
char *find_substr(char *string, char* substr) {
	char* start = string;

	while(*string){
		if(*string == *substr && *string +1 == *substr +1 && *string +2 == *substr +2)
			return string;
		*string++;
	}

	if(!*substr)   //if substring is empty
		return start;

	return NULL;
}