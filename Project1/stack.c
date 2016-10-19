/*
** Implementation of Stack library
**
** Tessa(Hyeri) Song(songt@student.unimelb.edu.au)
** Thursday 26 March 2015 11:00:00 AEDT
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stack.h"

#define TRUE 1
#define FALSE 0
#define SIZE 100	// Initial size of stack


/* create a new, empty stack */
Stack *stack_new(){
	Stack* s = (Stack*)malloc(sizeof(Stack));
	assert(s);
	
	s->A = (void **)malloc(sizeof(void *)*SIZE);
	assert(s->A);
	
	s->size = SIZE;
	s->top = -1;
	
	return s;
}


/* push item onto stack s */
void stack_push(Stack *s, void *item){
	// check if the stack is full or not and if it is, double the size
	if(s->top == (s->size-1)){
		s->A = (void**)realloc(s->A, sizeof(void*)*(s->size*2));
		assert(s->A);
		(s->size)*=2;
	}
	
	//push the item
	(s->top)+=1;
	s->A[s->top] = item;
	
}


/* pop item from stack s */
void *stack_pop(Stack *s){
	int top = s->top;

	if(stack_isEmpty(s))
		return NULL;
	
	//pop the item and decrease top by 1
	void * item = s->A[top];
	s->A[top] = NULL;
	(s->top)-=1;
	
	return item;
	
}


/* return 1 if stack s is empty, else 0 */
int stack_isEmpty(Stack *s){
	if(s->top == -1){
		return TRUE;
	}else{
		return FALSE;
	}
}


/* print whole stack */
void stack_print(Stack *s, void(printFn)(void * item)){
	int num = s->top;
	int i;
	
	if(stack_isEmpty(s))
		return;
	
	for(i = 0; i<=num; i++){
		printFn(s->A[i]);
	}	
}

/* free dynamically allocated stack */
void stack_free(Stack *s){
	free(s->A);
	free(s);
}



