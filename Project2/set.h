/*
** Set module
** This module takes Graph struct as an input and builds sets with it
** Eventually, this will print out the smallest possible sets to cover all the
** items.
**
** Tessa Song
** Student ID : 597952
** Thu 14 May 2015
**
*/

#include"graph.h"
#include"heap.h"


typedef struct {
	int rootVtx; // root Vertex of this set
	int* vtxArr; // array of vertices this set has
	int arrLen; // length of the array above
	int maxLen; // maximun length of the array
} SetItem;


typedef struct {
	SetItem* sArr; // array of SetItem struct
	int n; // the number of items in this SetArr

} SetArr;


typedef struct {
	int* rootVtxArr; // array of rootVtxs of sets which have the specific item. 
	int n; // the number of items in the array above
} Frqc;


//prototypes

SetArr* buildSets(Graph *g, int* arrVts, int len, int stdDist);
void printMimSets(SetArr* setArr, int numElement);
void destroySets(SetArr* setArr);













