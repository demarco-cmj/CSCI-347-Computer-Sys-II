/* Write a program to multiply two matrices using pthreads.
 Matrix Multiplication: Matrix C of size (x by z)  =  Matrix A of size (x by y) times Matrix B of size (y by z).
 
 * Example: Matrix A of size 2 by 3, Matrix B of size 3 by 2
              A = 1     1     5
                  2     4     2
              B = 0     2
                  5     1
                  0     5
 Then C = A * B = 5     28
                  20    18
 
 *It will generate random values for the elements of matrix A of size x by y and matrix B of size y by z
 *It will compute matrix C that is the result of multiplying matrix A by matrix B by using pthreads.
 *It will print the original matrices and the result matrix and show elapsed time.
 */

#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <sys/time.h>

/* Matrices dimensions */
#define  Dim_X  2 //RowA, RowC
#define  Dim_Y  3 //ColA, RowB
#define  Dim_Z  2 //ColB, ColC

#define Num_of_Threads  8

struct mm_thread_data {
  int start;
  int work;
  double *A;
  double *B;
  double *C;
};

/*
The thread_fn function shall compute the data, i.e., dot product rows and columns, in the range of start to start+work. The computed data shall be stored in matrix C. Matrices A and B are not to be modified
 */
void * thread_fn ( void *arg )
{

    return NULL;
}

/* Create Num_of_Threads threads to multiply the matrices A and B.
 Compute start and size of work done by the thread. Each thread shall process equal(or almost equal) part  of the matrix multiplication.
 Size of work shall be equal to (Dim_X * Dim_Z / Num_of_Threads). Make sure to consider the case where Dim_X * Dim_Z / Num_of_Threads does not result in a whole number.
 */
void multiply_matrices (double *A, double *B, double *C)
{
  //Check for matrix size compatibility
  if(Dim_X != Dim_Z){
    printf("These matricies cannot be multiplied!\n");
    exit(0);
  }

  //Multiply
  for(int i = 0; i < Dim_X; i++){
    for(int j = 0; j < Dim_Z; j++){
      double sum = 0;
      for(int k = 0; k < Dim_Y; k++){
        sum = sum + A[i * Dim_Y + k] * B[k * Dim_Z + j];
      }
      //printf("Num: %f \n", sum);
      C[i * Dim_Z + j] = sum;
    }
  }
  
}

/* Print a matrix of size x by y in the following format: one row per line with a tab space between each number. (Example output of printing a matrix of size 2 by 2)
 Row 0:           1          1
 Row 1:           5          2
 */
void print_matrix (double *A, int x, int y)
{
  int index = 0;
  for(int row = 0; row < x; row++){
    printf("Row %i: ", row);
    for(int col = 0; col < y; col++){
      printf("%f ", A[index]);
      index++;
    }
    printf("\n");
  }
}

/* Generate random data for a matrix of size x by y
 You can use the rand function.
 */
void generate_matrix (double *A, int x, int y)
{
  double temp;

  for(int i = 0; i < x * y; i++){
      temp = rand() % 10;
      A[i] = temp;
      //printf("%f \n", temp);
  }
}
  
/*The driver of the program.
 * Generate matrix A and matrix B using generate_matrix.
 * Multiply matrix A by matrix B using multiply_matrices.
 * Print matrix A, matrix B, and matrix C using print_matrix.
 * Compute and print the elapsed time in .3 precision.
 */
int main (int argc, char ** argv)
{
  // Allocate memory for the matrices A, B and C
  struct mm_thread_data data;
  data.A = malloc(sizeof(double) * Dim_X * Dim_Y);
  data.B = malloc(sizeof(double) * Dim_Y * Dim_Z);
  data.C = malloc(sizeof(double) * Dim_Y * Dim_Z);

  //Generate matrices A and B

  generate_matrix(data.A, Dim_X, Dim_Y);
  generate_matrix(data.B, Dim_Y, Dim_Z);

  //Compute C as the result of A multiplied by B
  multiply_matrices(data.A, data.B, data.C);

  printf ("-------------- orignal A matrix ------------------\n");
  //print matrix A
  print_matrix(data.A, Dim_X, Dim_Y);
  printf ("-------------- orignal B matrix ------------------\n");
  //print matrix Bich will perform the following functions.
  print_matrix(data.B, Dim_Y, Dim_Z);
  printf ("--------------  result C matrix ------------------\n");
  //print matrix C
  print_matrix(data.C, Dim_X, Dim_Z);
    
  //print the elapsed time
  return 0;
}
