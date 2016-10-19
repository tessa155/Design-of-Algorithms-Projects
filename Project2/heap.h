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


#define MIN_PRIORITY 1
#define MAX_PRIORITY 0

#define NO_CHILD 0
#define NOT_IN_HEAP 0
#define IN_HEAP 1

typedef int uint; 

typedef struct {
	float key; // the key for deciding position in heap	
	uint dataIndex; // the payload index provided by the calling program
} HeapItem;


typedef struct {
	HeapItem *H; // the underlying array
	uint *map; // map[i] is index into H of location of payload with dataIndex == i
	uint n; // the number of items currently in the heap
	uint size; // the maximum number of items allowed in the heap
	int prort; //flag which decides either MIN OR MAX priority 
} Heap;


// prototypes
Heap *createHeap(int num, int prort);
void insert(Heap *h, uint dataIndex, float key);
uint peek(Heap *h);
float peekKey(Heap *h);
uint removeRoot(Heap *h);
void changeKey(Heap *h, uint dataIndex, float delta);
float peekKeyWithVtx(Heap* h, uint dataIndex);
void destroyHeap(Heap *h);
int isInHeap(Heap* h, uint dataIndex);
