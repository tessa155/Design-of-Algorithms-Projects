/*
** Main file for the set cover problem
**
** This program is printing out the possible site vertices to build schools
**  anaylsing integers in the given text input so that every student can 
**  commute to school within 1 km
**
** Tessa Song
** Student ID : 597952
** Thu 14 May 2015
**
*/


#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#define DISTANCE 1000



int main(int argc, char *argv[]){
	int numHouse, numSite = 0;
	int v1, v2, dist;
	
	
	if(scanf("%d %d", &numHouse, &numSite)!=2){
		fprintf(stderr, "Invalid Input File\n");
		exit(EXIT_FAILURE);
	}
	
	// Build a graph
	Graph* g = graph_new(numHouse+numSite);
	
	// add egdes to the graph checking range
	while (scanf("%d %d %d", &v1, &v2, &dist) == 3){
		graph_add_edge(g, v1, v2, dist, NULL);
		graph_add_edge(g, v2, v1, dist, NULL);	
	}	

	
	// check if this graph is fully connected using dfs
	int comp = graph_dfs(g,0);
	if(comp != 1){
		fprintf(stderr, "This graph is not connected.\n");
		fprintf(stderr, "This graph consists of %d components.\n", comp);
		exit(EXIT_FAILURE);
	}
	
	/*---------Validity Checked------------*/
	
	
	
	
	int arr[numSite];
	int i;
	for(i = 0;i<numSite;i++){
		arr[i] = numHouse+i;
	}
	
	// divide the graph into sets
	SetArr* setArr =  buildSets(g, arr, numSite, DISTANCE);
	
	// print out the possible site vertices
	printMimSets(setArr, numHouse);
	
	// free allocated memory
	destroyGraph(g);
	destroySets(setArr);
	
	
	
	return 0;
}












