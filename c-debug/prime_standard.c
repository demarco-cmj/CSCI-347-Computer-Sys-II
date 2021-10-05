//Connor DeMarco
//1/13/21

#include <stdio.h>

int primeNumbers[15];  /* primeNumbers[i] will be 1 if i is prime, 0 otherwise */
int upperBound; /* check all numbers up through this one for primeness */

void checkPrime(int k, int primeNumbers[]) {
  int j;
  /*checkPrime simply itterates through all of the potential divisors for k between 1 and sqrt(k). 
  The function uses the modulus operation to check whether or not j is an even divisor. This all determines
  if k is a prime number or not.*/
 
  j = 2; //Being devisable by 1 does not indicate if num is prie, therfore j starts at 2.
  while (j * j <= k) {
    if (primeNumbers[j] == 1){
      if (k % j == 0)  {
        primeNumbers[k] = 0;
        return;
      } /* if (k % j == 0) */
    } /* if (primeNumbers[j] == 1) */
    j++;
  } /* while (1) */

  /* if we get here, then there were no divisors of k, so it is prime */
  primeNumbers[k] = 1;

}  /* checkPrime() */

int main() {
  int i;

  //Get user input
  printf("Enter upper bound:\n");
  scanf("%d", &upperBound);

  
  upperBound = 50;
  primeNumbers[1] = 1;
  primeNumbers[2] = 1;
  
  //Checks each odd number starting with three if it is a prime number. Calls checkPrime, prints 
  for (i = 3; i <= upperBound; i += 2) {
    checkPrime(i, primeNumbers);
    if (primeNumbers[i]) {
      printf("%d is a prime\n", i);
    } /* if (primeNumbers[i]) */
  } /* for (i = 3; i <= upperBound; i += 2) */
  return 0;
}
