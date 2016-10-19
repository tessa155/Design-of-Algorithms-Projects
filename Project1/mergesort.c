/*
** Implementation of mergesort using stack library
**
** Tessa(Hyeri) Song(songt@student.unimelb.edu.au)
** Thursday 26 March 2015 11:00:00 AEDT
** 
** Attribution
**   The general structure of this script basically came from the script
**   written by Olac Fuentes.
**   See http://www.cs.utep.edu/ofuentes/cs2302/fall11/nonRecursiveMergesort.txt
**   for further information.
**   
**   The source code on http://www.sanfoundry.com/c-program-merge-sorted-array/
**   was consulted for the function of mergeTwoPart
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "mergesort.h"

#define TRUE 1
#define FALSE 0

/* create a new mergeFrame */
mergeFrame* mergeFrameNew(int sorted, int first, int last){
    mergeFrame *mptr = (mergeFrame *)malloc(sizeof(mergeFrame));
    assert(mptr);

    mptr->sorted = sorted;
    mptr->first = first;
    mptr->last = last;

    return mptr;
}


/* merge the two sorted sub arrays (from first to mid, from mid+1 to last) */
void mergeTwoPart(void** A, int first, int last, int(cmp)(void *, void*)){
	int fIdx = first; // first index of the first sub array
	int mid = (first+last)/2;
	int sIdx = mid+1; // first index of the second sub array
	int tIdx = 0; // index of a temp array
	int i, j;
	
	void** tempArr = (void**)malloc(sizeof(void*)*(last-first+1));
	assert(tempArr);
	
	//compare elements in the two arrays one by one and copy them to 
	//the temporary array
	while(fIdx <= mid && sIdx <= last){
		if(cmp(A[fIdx], A[sIdx])<=0)
			tempArr[tIdx] = A[fIdx++];
		else
			tempArr[tIdx] = A[sIdx++];
		tIdx++;
	}
	
	//At this point one of the two sub arrays has been copied to the temp array
	//completely
	
	//copy the rest of elements in either first or second sub array
	//to the temp array
	if(fIdx > mid){
		for(i=sIdx; i<=last; i++, tIdx++)
			tempArr[tIdx] = A[i];
	} else{
		for(i=fIdx; i<=mid; i++, tIdx++)
			tempArr[tIdx] = A[i];
	}
	
	//transfer all the elements of the temp array to the original array
	for(i=first, j = 0; i<=last; i++, j++){
		A[i] = tempArr[j];
	}
	free(tempArr);
}


/* sort the array using merge sort algorithm */
void myMergesort(void **A, int n, int(cmp)(void *, void*)) {
	Stack* s = stack_new();
	mergeFrame* mptr;
	int first, last;
	
	stack_push(s, mergeFrameNew(FALSE,0,n-1));
	
	//run a loop until the stack gets empty
	while (!stack_isEmpty(s)){			
		mptr = (mergeFrame*)stack_pop(s);
		first = mptr->first;
		last = mptr->last;
		
		// if the two sub arrays have already been sorted, merge them
		if (mptr->sorted){
			mergeTwoPart(A,first,last,cmp);
			free(mptr);
		}
		else{
			// if the stack has more than 1 element
			if (first < last){
				int mid = (first + last)/2;
				//push a stack for the array and set sorted as True and
				//push two stacks for the two sub arrays and set sorted as False
				stack_push(s, (mergeFrameNew(TRUE,first,last)));
				stack_push(s, (mergeFrameNew(FALSE,first,mid)));
				stack_push(s, (mergeFrameNew(FALSE,mid+1,last)));
			}else{
				free(mptr);
			}
		}
	}
	//free the stack
	stack_free(s);
}

