//Connor DeMarco
//CSCI 347
//3/15/21

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
#define  Dim_X  200 //RowA, RowC
#define  Dim_Y  300 //ColA, RowB
#define  Dim_Z  200 //ColB, ColC

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
  struct mm_thread_data *data = (struct mm_thread_data *)arg;
  int start = data->start;
  int work = data->work;
  double *A = data->A;
  double *B = data->B;
  double *C = data->C;

  //Multiply
  for(int i = start; i < start + work; i++){
    for(int j = 0; j < Dim_Z; j++){
      for(int k = 0; k < Dim_Y; k++){
        C[i * Dim_Z + j] += A[i * Dim_Y + k] * B[k * Dim_Z + j];
      }
      //printf("Num: %f \n", sum);
    }
  }
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

  //Create Threads and Thread contents
  pthread_t arr[Num_of_Threads];
  struct mm_thread_data data[Num_of_Threads];
  double work = (Dim_X * Dim_Z)/Num_of_Threads;

  //Loop through each thread
  for(int thread = 0; thread < Num_of_Threads; thread++){
    //printf("Creating thread: %i\n", thread);

    data[thread].A = A;
    data[thread].B = B;
    data[thread].C = C;
    data[thread].start = work * thread;
    data[thread].work = work;

    if((Num_of_Threads - thread) == 1)
      data[thread].work = Dim_X * Dim_Z - data[thread].start;

  //make sure thread is being created successfully //PROBLEM HERE
    if (pthread_create(&arr[thread], NULL, thread_fn, (void *)(&data[thread])) != 0){
        printf("Error while creating thread #%i", thread);
        exit(0);
    }
  }

  //Wait for threads to complete
  for (int j = 0; j < Num_of_Threads; j++){
    void* temp;
    pthread_join(arr[j], &temp);
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
      printf("%.0lf ", A[index]);
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
      temp = rand() % 100;
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
  //Local Variables
  double totalTime = 0.0;
  clock_t start, end;

  // Allocate memory for the matrices A, B and C
  struct mm_thread_data data;
  int buffer = Dim_X; //Was having a buffer overflow issue, this is a cheap workaround to dynamically allocate enough mem
  if(Dim_X < Dim_Y) //Will always compile and run but is very slow for larger matricies
    buffer = Dim_Y;

  data.A = malloc(sizeof(double) * Dim_X * Dim_Y * buffer);
  data.B = malloc(sizeof(double) * Dim_Y * Dim_Z * buffer);
  data.C = malloc(sizeof(double) * Dim_X * Dim_Z * buffer);

  //Generate matrices A and B
  generate_matrix(data.A, Dim_X, Dim_Y);
  generate_matrix(data.B, Dim_Y, Dim_Z);

  //Compute C as the result of A multiplied by B
  start = clock();
  multiply_matrices(data.A, data.B, data.C);
  end = clock();
  totalTime += (double)(end - start) / CLOCKS_PER_SEC;
  totalTime /= Num_of_Threads;

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

  printf("\nTime elapsed: %.3lf seconds\n", totalTime);
  
  //Free memory
  free(data.A);
  free(data.B);
  free(data.C);
  
  return 0;
}
