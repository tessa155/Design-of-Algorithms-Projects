/*
** Header for COMP20007 Assignment 1
**
** Andrew Turpin
** Thu 26 Feb 2015 11:08:14 AEDT
**
** Added by Tessa(Hyeri) Song(songt@student.unimelb.edu.au)
** Thursday 26 March 2015 11:00:00
**
*/

//stack frame for quicksort
typedef struct {
	int first; // first index of the sub array
	int last; // last index of the sub array
} sortFrame;

//create a new sortFrame
sortFrame* sortFrameNew(int first, int last);

//sort the given array using quicksort algorithm
void myQuicksort(void **A, int n, int(cmp)(void *, void*));

//pick up three random elements and take the median as pivot
void* choosePivot(void **A, int first, int last, int(cmp)(void*, void*));
