/*
** Header for COMP20007 Assignment 1
**
** Andrew Turpin
** Thu 26 Feb 2015 11:08:14 AEDT
**
** Added by Tessa(Hyeri) Song(songt@student.unimelb.edu.au)
** Thursday 26 March 2015 11:00:00
*/

//stack frame for mergesort
typedef struct {
	//Indicates if the first and second half of the array have already been sorted 
	int sorted; 
	int first;  //first index
	int last;   // last index
} mergeFrame;

//merge the two sorted sub arrays (from first to mid, from mid+1 to last)
void mergeTwoPart(void** A, int first, int last, int(cmp)(void *, void*));

//create a new mergeFrame
mergeFrame* mergeFrameNew(int sorted, int first, int last);

//sort the array using merge sort algorithm
void myMergesort(void **A, int n, int(cmp)(void *, void*));



