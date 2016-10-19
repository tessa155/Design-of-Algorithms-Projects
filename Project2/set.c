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


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include <limits.h>
#include"set.h"


// prototypes
void pruneSet(Graph *g, SetItem* setItem, int stdDist, int len);


/*
** Builds sets from the given Graph struct on the basis of arrVtx(they become
** root vertices) and stdDist
*/
SetArr *buildSets(Graph *g, int* arrVtx, int len, int stdDist){

	// initialise setArr
	SetArr* setArr = (SetArr *)malloc(sizeof(SetArr));
	assert(setArr);
	
	setArr->sArr = (SetItem *)malloc(sizeof(SetItem)*len);
	assert(setArr->sArr);
	
	setArr->n = len;
	
	
	// initialise each set 
	int i;
	for(i = 0;i<len;i++){
		setArr->sArr[i].rootVtx = arrVtx[i];
		setArr->sArr[i].vtxArr = (int *)malloc(sizeof(int)*
									g->number_of_vertices);
		assert(setArr->sArr[i].vtxArr);
		
		setArr->sArr[i].arrLen = 0;
		setArr->sArr[i].maxLen = g->number_of_vertices;

	}

		
	// prune sets using the given graph
	// Dijakstra's Algorithm is used
	for(i = 0;i<len;i++){
		pruneSet(g, &(setArr->sArr[i]), stdDist, len);
	}
	
	return setArr;
	
}


/*
** prunes a set and put the array of vertices of this set into setItem
*/
void pruneSet(Graph *g, SetItem* setItem, int stdDist, int len){
	
	// create heap
	Heap *h = createHeap(g->number_of_vertices, MIN_PRIORITY);

	// insert heapItem into the heap
	int i;
	for(i = 0; i<g->number_of_vertices; i++){
		if(i == setItem->rootVtx){
			insert(h, i, 0);
		}else{
			insert(h, i, INT_MAX);
		}
	}
	
	
	int idx;
	float pKey;
	float crtKey, udtdKey;

	//find out all the vertices within the stdDist using heap(priority queue)
	while(h->n){
		
		pKey = peekKey(h);
		
		// if the smallest key is bigger or equal to stdDist, then stop
		if(pKey > stdDist)
			break;
		
		// maximum vertex index of item
		int maxIdx = g->number_of_vertices - len;
		
		// put the dataIndex into the setItem but exclude if it is root vertex
		if(peek(h) != setItem->rootVtx){
			if(peek(h) < maxIdx){
				setItem->vtxArr[setItem->arrLen++] = peek(h);
			}
		}
		
		
		idx = removeRoot(h);
		
		for(i = 0; i<g->vertices[idx].num_edges; i++){
			if(graph_has_edge(g,idx,g->vertices[idx].edges[i].u)){
			
				// no need to update the removed vertices
				if(isInHeap(h, g->vertices[idx].edges[i].u)){
					crtKey = peekKeyWithVtx(h, g->vertices[idx].edges[i].u);
					udtdKey = pKey + g->vertices[idx].edges[i].dist;
					
					// if updated key is less than current key, change it
					if( crtKey > udtdKey ) 
						changeKey(h, g->vertices[idx].edges[i].u, udtdKey);
				}
			}
		}
				
	}
	
	destroyHeap(h);
}


/*
** prunes a set and put the array of vertices of this set into setItem
*/
void printMimSets(SetArr* setArr, int numElement){
	
	Frqc frqcArr[numElement];
	int mimSetArr[setArr->n];
	int msaLen = 0;
	
	// create an array which consists of Frqc structs
	int i, j;
	for(i = 0;i<numElement;i++){
		frqcArr[i].rootVtxArr = (int *)malloc(sizeof(int)*setArr->n);
		frqcArr[i].n = 0;
	}
	
	// fill up the frqcArr with the given setArr
	SetItem item;
	for(i = 0;i<setArr->n;i++){
		item = setArr->sArr[i];
		for(j = 0; j<item.arrLen; j++){
			frqcArr[item.vtxArr[j]].rootVtxArr[frqcArr[item.vtxArr[j]].n++]
			= item.rootVtx;
		}
	}

	
	// if there is at least one vertex which cannot be covered by this graph
	// then, the minimum sets cannot be found.
	int isPossible = 1;
	for(i = 0;i<numElement;i++){
		if(frqcArr[i].n == 0){
			isPossible = 0;
			break;
		}
	}
	if(!isPossible){
		fprintf(stderr, "More possible sites are needed.\n");
		exit(EXIT_FAILURE);
	}
	

	
	// build a heap on a basis of the number of uncovered items.
	// 'key' refers to the number of uncovered items.
	Heap *h = createHeap(setArr->n, MAX_PRIORITY);
	for(i = 0; i<setArr->n; i++){
		insert(h, i, setArr->sArr[i].arrLen);
	}
	
	
	// fill mimSetArr with greedy approach
	while(h->n){
		
		// if all the elements are covered then stop
		int allZero = 1;
		for(i = 0;i<numElement;i++){
			if(frqcArr[i].n != 0){
				allZero = 0;
				break;
			}
		}
		
		if(allZero)
			break;

		
		int dataIndex = removeRoot(h);
		// put this root vertex
		mimSetArr[msaLen++] = dataIndex+numElement;
		

		
		float crtKey;
		int vtxIdx, rootIdx;
		for(i = 0;i<setArr->sArr[dataIndex].arrLen;i++){
			vtxIdx = setArr->sArr[dataIndex].vtxArr[i];
			
			// if the vtxIdx not covered yet
			if(frqcArr[vtxIdx].n != 0){
				for(j = 0;j<frqcArr[vtxIdx].n;j++){
					
					// no need to change the key of the one already removed
					rootIdx = frqcArr[vtxIdx].rootVtxArr[j];
					if(isInHeap(h, rootIdx-numElement)){

						// reduce the key by one
						crtKey = peekKeyWithVtx(h, rootIdx-numElement);
						changeKey(h, rootIdx-numElement, crtKey-1);
					}
				}
				
				frqcArr[vtxIdx].n = 0;
			}
			
		}
			
	}
	
	// print out the possible mimimun sets
	for(i = 0;i<msaLen;i++){
		printf("%d\n", mimSetArr[i]);
	}

	destroyHeap(h);

}



/*
** free all the allocated memory 
*/
void destroySets(SetArr* setArr){
	int i;
	for(i = 0;i<setArr->n;i++){
		free(setArr->sArr[i].vtxArr);
	}
	
	free(setArr->sArr);
	free(setArr);
	
}












