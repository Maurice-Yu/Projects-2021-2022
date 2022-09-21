// optimized versions of matrix A^T*A operation
#include "matvec.h"
#include <string.h>
#include <stdlib.h>
int matata_VER1(matrix_t mat, matrix_t ans) {
  // YOUR CODE HERE// Baseline version from matata_base.c
  short size=mat.rows;    // instead of havving to access matrows every time i put it into a size variable
  int *holder=mat.data;  //by having a pointer to the data you dont have to access the struct takes one step off of getting the data
  int *holder2=ans.data;	
  int *x;	//used to hold a computed value speeds up so when accessing the value you just pull from x instead of computeing it every time
  int *y;	//same
  int constant;	//same	
  int constant2;	//same
  int lead;	//this holds the lead value that will be used alot

  for(short i=0; i<size; i++){		//sets answers to zero using memset
    memset(&holder2[i*size],0,(size*4));
    }
  for(short i=0;i<size;i++)	
  {
     constant=size*i;		//this holds the spot for the collums
     
    for(short j=0;j<size;j++)
   {
	   constant2 = size*j;     // this holds the collum spot
	   lead=(holder[constant+j]);	//collumspot + row spot
	   x=&(holder2[constant2]);	//by putting x as a pointer to the data you eliminate the need to unnesisary calcluations to get fetch the data 
	   y=&(holder[constant]);  //same
   for(short k=0;k<size;k++)
   {
   x[k]= x[k]+lead*y[k];   //the use of variables holding values makes it so when you access data all you need is one variable instead of having lets say holder[constant+whatever] you dont have to wait for the calculation of constant+whatever to run so you increase pipelining and decrease unnecisary calculations
   }
   
   }                        
}

  return 0;                                     // return success
}

 
// ADDITIONAL VERSIONS HERE

int matata_OPTM(matrix_t mat, matrix_t ans) {
  if(mat.rows != mat.cols ||                    // must be a square matrix for A^T*A
     mat.rows != ans.rows ||
     mat.cols != ans.cols)
  {
    printf("matata_OPTM: dimension mismatch\n");
    return 1;
  }

  // Call to some version of optimized code
  return matata_VER1(mat, ans);
  // return matata_VER2(mat, ans);
}
