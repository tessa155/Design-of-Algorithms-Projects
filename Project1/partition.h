/*
** Partition A[0..n-1] so that 
**  all elements less than ** *pivot are in A[0..k-1] and 
**  all elements not less than *pivot ** are in A[k..n-1]. 
** cmp should be used for comparisons.
**
** @return k
**
** Andrew Turpin
** Thu 26 Feb 2015 08:42:06 AEDT
**
** Added by Tessa(Hyeri) Song(songt@student.unimelb.edu.au)
** Thursday 26 March 2015 11:00:00
**
*/

void swap(void** d1, void** d2); // swap the values of two given pointers

//partition the given array based on the pivot value
int partition(void **A, int n, void *pivot, int (cmp)(void *, void *));

