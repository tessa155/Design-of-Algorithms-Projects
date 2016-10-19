/*
** Implementation of quicksort using stack library
**
** Tessa(Hyeri) Song(songt@student.unimelb.edu.au)
** Thursday 26 March 2015 11:00:00 AEDT
**
** Attribution
**   Basically, any source code was not consulted to implement 
**   this script directly.
**   However, this script was built after the script for mergesort 
**   was implemented which had refered to the code written by Olac Fuentes
**   and those two scripts(merge, quick) have similarities especially
**   in respect of using a stack library.
**   Therefore, this script was influenced indirectly by the author's code.
**
**   See http://www.cs.utep.edu/ofuentes/cs2302/fall11/nonRecursiveMergesort.txt
**   for further information.
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "quicksort.h"
#include "stack.h"
#include "partition.h"

/* create a new sortFrame */
sortFrame* sortFrameNew(int first, int last){
    sortFrame *sptr = (sortFrame *)malloc(sizeof(sortFrame));
    assert(sptr);

    sptr->first = first;
    sptr->last = last;

    return sptr;
}


/* pick up three random elements and take the median as pivot */
void* choosePivot(void **A, int first, int last, int(cmp)(void*, void*)){
	int n = (last-first)+1;
	void* arr[3];
	int i;
	
	//pick up three random elements 
	for(i = 0;i<3;i++){
		arr[i] = A[(rand()%n)+first];
	}
	
	//sort the three elements and return the median
	if(n<3){
		//if the length of the array is less than 3, pick up the first one 
		//as pivot
		return A[first];
	}else{
		if( cmp(arr[0], arr[1]) > 0 ) 
			swap(&arr[0], &arr[1]);
		
		if( cmp(arr[0], arr[2]) > 0 )
			swap(&arr[0], &arr[2]);
		
		if( cmp(arr[1],arr[2]) > 0 )
			swap(&arr[1], &arr[2]);
		
		return arr[1];
	}
	
}

/* sort the given array using quicksort algorithm */
void myQuicksort(void **A, int n, int(cmp)(void *, void*)) {
	Stack* s = stack_new();
	sortFrame* sptr;
	int pIdx; // index of pivot
	int first, last; //first and last index of a stack frame
	void* pivot;
	
	stack_push(s, sortFrameNew(0,n-1));
		
	//run a loop until the stack gets empty
	while (!stack_isEmpty(s)){
		sptr = (sortFrame*)stack_pop(s);
		first = sptr->first;
		last = sptr->last;
		
        // if there are more than one element             
		if (first < last){
			pivot = choosePivot(A, first, last, cmp);
			// partition the array A+first based on the picked pivot
			pIdx = partition(A+first, last-first+1, pivot, cmp);
			pIdx+=first;

			//if the pivot is located at the first index
			if(pIdx == first){
				stack_push(s, sortFrameNew(pIdx+1,last));
			}
			//if the pivot is located at the last index
			else if(pIdx == last){
				stack_push(s, sortFrameNew(first, pIdx-1));
			}
			//if the pivot is located between the first and last index
			else{
				stack_push(s, (sortFrameNew(first,pIdx-1)));
				stack_push(s, (sortFrameNew(pIdx+1, last)));
			}
		}
		//free the frame
		free(sptr);
	}
	//free the stack
	free(s);
}

