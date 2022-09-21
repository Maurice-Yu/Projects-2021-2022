// Complete this main to benchmark the search algorithms outlined in
// the project specification
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef union search_t //3 unions for the different function types
{
	int (*universal)(void *x,int,int);  //universal function prototype for easy calling
	int (*array)(int x[],int,int);
	int (*list)(list_t *x,int,int);
	int (*tree)(bst_t *x,int,int);
	
} search_t;
typedef union setup_t
{
	void *(*universal)(int);
	int *(*array)(int);
	list_t *(*list)(int);
	bst_t *(*tree)(int);
}
setup_t;
typedef union cleanup_t
{
	void (*universal)(void *x);
	void (*array)(void *ptr);
	void (*list)(list_t *x);
	void (*tree)(bst_t *x);
}
cleanup_t;
typedef struct searchalgs_t  //main struct that holds info
{
	char *name;
	char *type;
	char *var;  //type to be checked with from the function call 
	int bool;
	search_t search;
	setup_t setup;
	cleanup_t free;
}
searchalgs_t;
searchalgs_t algs[]={
	{"Linear Array Search", "array",  "la", 1,
      (search_t) linear_array_search, (setup_t)make_evens_array, (cleanup_t)free},
	{"Linked List Search",  "list",   "ll", 1,
    (search_t) linkedlist_search,   (setup_t) make_evens_list,  (cleanup_t) list_free},
    {"Binary Tree Search", "tree", "bt",1,
	(search_t) binary_tree_search, (setup_t) make_evens_tree,(cleanup_t) bst_free},
	{"Binary Array Search", "binary", "bl",1, 
	(search_t) binary_array_search, (setup_t) make_evens_array, (cleanup_t) free}
};
			
int main(int argc, char *argv[]){
  clock_t begin,end;
  int min=atoi(argv[1]);
  int max=atoi(argv[2]);
  int loop=atoi(argv[3]);

  int x=2;
  
  for (int i=0;i<min-1;i++)  //makes it a power of two
  {
  x=x*2;
  }
  min=x;
  x=2;
  for (int i=0;i<max-1;i++)
  {
  x=x*2;
  }
  max=x;
	if (argc>4)  //if there are more then 3 args then it will figure out which ones to keep if not they all will run
	{
	algs[0].bool=0;
	algs[1].bool=0;
	algs[2].bool=0;
	algs[3].bool=0;
	for (int i=1;i<argc-3;i++)
	{
		for (int j=0;j<4;j++)
		{
			char *holder =  argv[i+3];
			if(!strcmp(algs[j].var,holder))
			{
				algs[j].bool=1;
			}
		}
	}
}
for(int k=min;k<=max;k=k*2)    //iterates through min through max
		{
	for(int i=0;i<4;i++)
	{	
		if(algs[i].bool)
		{
			 int searches = 0;	
			 void *data = algs[i].setup.universal(k);  //this holds the datastructure
			 begin = clock();
			 for(int y=0;y<loop;y++)
				{
				for(int j=0;j<=(k*2-1);j++)
				{
				searches+=algs[i].search.universal(data,k,j);
				}
				}
			  end = clock();
		 	  double cpu_time =((double) (end-begin)/CLOCKS_PER_SEC);  //prints the output
			  printf("\nsearch_type: %s length: %d searches:%d time: %lf",algs[i].name,k,searches*2,cpu_time);
			  algs[i].free.universal(data);
		}
		

	}
	printf("\n");
}
	return 0;
}

	
