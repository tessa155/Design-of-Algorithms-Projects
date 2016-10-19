/*
** Heap module
** Basic prototypes and structs were designed by Andrew Turpin 
** for workshop 4 of COMP20007 
**
** Made to implement priority queue.
** Both Min and Max priority queues are available.
** Assume all the dataIndexs are integers and unique.
** 
** Attribution: 
**  Some of the codes in this script were refered from
**  http://robin-thomas.github.io/min-heap/
**
** Tessa Song
** Student ID : 597952
** Thu 14 May 2015
**
*/


#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"heap.h"


// prototypes
int getParentIdx(int idx);
int getLeftChildIdx(int idx);
int getRightChildIdx(int idx);
int getHiPriChildIdx(Heap * h, int idx);
void shiftUp(Heap* h, int idx, HeapItem item);
void shiftDown(Heap* h, int idx, HeapItem item);



/*
** Create heap whose size is 'num' and set the priority as given
** (min or max)
*/
Heap *createHeap(int num, int prort){
	
	assert(num>0);
	
	Heap * h = (Heap *)malloc(sizeof(Heap));
	assert(h);
	
	h->H = (HeapItem *)malloc(sizeof(HeapItem)*num);
	assert(h->H);
	
	h->map = (uint *)malloc(sizeof(uint)*num);
	assert(h->map);
	
	h->n = 0;
	h->size = num;
	h->prort = prort;
	
	return h;
	
}



/*
** Insert element into the heap 
*/
void insert(Heap *h, uint dataIndex, float key){
	assert(h);

	// check the capacity first. If not enough, realloc.
	if(h->n == h->size){
		h->H = (HeapItem *)realloc(h->H,sizeof(HeapItem)*h->size*2);
		assert(h->H);
		h->map = (uint *)realloc(h->map,sizeof(uint)*h->size*2);
		assert(h->H);
		h->size *=2;
	}
	
	int idx = h->n;
	HeapItem item = {key, dataIndex};
	
	// shift up the item
	shiftUp(h, idx, item);

	h->n++;
	
}



/*
** remove the root element in the given heap and return its dataIndex
*/
uint removeRoot(Heap *h){
	assert(h);
	assert(h->n>0);
	
	uint dataIndex = (h->H[0]).dataIndex;
	HeapItem item = h->H[h->n-1];
	
	// shift down the item
	shiftDown(h, 0, item);
	
	h->n--;
	h->map[dataIndex] = -1;
	
	return dataIndex;
		
}



/*
** change the key of the given heap element into delta
*/
void changeKey(Heap *h, uint dataIndex, float delta){
	assert(h);
	assert(dataIndex < h->size);

	//get the index of the element using map array
	int idx = h->map[dataIndex];
	
	float orgnKey = h->H[idx].key;
	
	//change the key
	h->H[idx].key = delta;
	HeapItem item = h->H[idx];
	

	// This deals with all the possible four cases
	if(h->prort == MIN_PRIORITY && orgnKey > delta)
		shiftUp(h, idx, item);
	else if(h->prort == MIN_PRIORITY && orgnKey < delta)
		shiftDown(h, idx, item);
	else if(h->prort == MAX_PRIORITY && orgnKey > delta)
		shiftDown(h, idx, item);
	else if(h->prort == MAX_PRIORITY && orgnKey < delta)
		shiftUp(h, idx, item);
	
}



/*
** Return the dataIndex of the root element
*/
uint peek(Heap *h){
	assert(h);
	assert(h->n>0);
	
	return h->H[0].dataIndex;	
}



/*
** Return the key of the root element
*/
float peekKey(Heap *h){
	assert(h);
	assert(h->n>0);
	
	return h->H[0].key;
}



/*
** Return the key of the given dataIndex
*/
float peekKeyWithVtx(Heap* h, uint dataIndex){
	
	return h->H[h->map[dataIndex]].key;

}



/*
** Check if there the given dataIndex is in this heap
*/
int isInHeap(Heap* h, uint dataIndex){
	
	if(h->map[dataIndex] == -1){
		return NOT_IN_HEAP;
	}else {
		return IN_HEAP;
	}

}



/*
** free all the allocated memory
*/
void destroyHeap(Heap *h){
	assert(h);
	
	free(h->H);
	free(h->map);
	free(h);
	
}



/*
** shift up the HeapItem in the heap
*/
void shiftUp(Heap* h, int idx, HeapItem item){
	assert(h);
	
	int flag = 1;
	
	// if flag is 1 and it is not the root
	while(flag && idx != 0){
		float prtKey = h->H[getParentIdx(idx)].key;
		
		// deals with two possible cases (MIN or MAX)
		if( (h->prort == MIN_PRIORITY && item.key < prtKey) ||
			(h->prort == MAX_PRIORITY && item.key > prtKey) ){
		
			h->H[idx] = h->H[getParentIdx(idx)];
			h->map[h->H[idx].dataIndex] = idx;
			
			//update the idx
			idx = getParentIdx(idx);
			
		}else{
			flag = 0;
		}
	}
	
	//put the item at 'idx' in the heap
	h->H[idx] = item;
	h->map[item.dataIndex] = idx;
}



/*
** shift down the HeapItem in the heap
*/
void shiftDown(Heap* h, int idx, HeapItem item){
	assert(h);
	
	// this is going to be the idx for the HeapItem
	int parentIdx = idx;

	int childIdx;
	
	// if there is a child
	while(childIdx = getHiPriChildIdx(h, parentIdx)){
		
		// deals with two possible cases(MIN or MAX)
		if( (item.key <= h->H[childIdx].key && h->prort == MIN_PRIORITY) ||
			(item.key >= h->H[childIdx].key && h->prort == MAX_PRIORITY) ){
			break;
		}
		
		h->H[parentIdx] = h->H[childIdx];
		h->map[h->H[parentIdx].dataIndex] = parentIdx;
		
		// update parentIdx
		parentIdx = childIdx;
		
	}
	
	// put the item at 'parentIdx' in the heap
	h->H[parentIdx] = item;
	h->map[item.dataIndex] = parentIdx;
	
}



/*
** return the parent idx
*/
int getParentIdx(int idx){
	return (idx-1)/2;
}



/*
** return the left child idx
*/
int getLeftChildIdx(int idx){
	return idx*2+1;
}



/*
** return the right child idx
*/
int getRightChildIdx(int idx){
	return getLeftChildIdx(idx)+1;
}



/*
** return the child idx with higher priority
** result is different up to 'prort' of the heap
*/
int getHiPriChildIdx(Heap * h, int idx){
	assert(h);
	float leftCKey, rightCKey;
	
	// if left child idx is beyond the array
	if(getLeftChildIdx(idx) >= h->n){
		return NO_CHILD;
		
	// if there is only one child(left)
	}else if(getLeftChildIdx(idx) == h->n-1){
		return getLeftChildIdx(idx);
		
	}else{
		leftCKey = h->H[getLeftChildIdx(idx)].key;
		rightCKey = h->H[getRightChildIdx(idx)].key;
		
		// deals with two possible cases (MIN or MAX)
		// compares the two children 
		if((leftCKey > rightCKey && h->prort == MIN_PRIORITY) ||
			(leftCKey < rightCKey && h->prort == MAX_PRIORITY) ){
			return getRightChildIdx(idx);
		}else{
			return getLeftChildIdx(idx);
		}
		
	}
	
}


