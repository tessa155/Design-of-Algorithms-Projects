/*
** Implementation of partition
**
** Tessa(Hyeri) Song
** Thursday 26 March 2015 11:00:00 AEDT
** 
** Attribution
** 	This program was originally written by Alistair Moffat, as an example for 
** 	the book "Programming, Problem Solving, and Abstraction with C", Pearson
** 	SprintPrint, Sydney, Australia, 2003.
**  See http://www.cs.mu.oz.au/~alistair/ppsaa/ for further information.
**
*/

#include<stdio.h>
#include<assert.h>
#include "partition.h"

/* partition the given array based on the pivot value */
int partition(void **A, int n, void * pivot, int (cmp)(void*, void*)){
	int next=0, fe=0, fg=n, outcome;
	
	while (next<fg) {
		if ((outcome = cmp(A[next], pivot)) < 0) {
			swap(A+fe, A+next);
			fe += 1;
			next += 1;
		} else if (outcome > 0) {
			fg -= 1;
			swap(A+next, A+fg);
		} else {
			next += 1;
		}
	}
	
	assert(0<=fe && fe<fg && fg<=n);
	
	//return the index of the pivot
	return fe;
}


/* swap the values of the two given pointers */
void swap(void** ptr1, void** ptr2){
	void* temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

