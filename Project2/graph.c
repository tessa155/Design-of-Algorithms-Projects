/*
** Graph data type
** Uses an adjacency list representation (arrays for lists).
** Written for workshop 3 of COMP20007
**
** Andrew Turpin
** Tue 17 Mar 2015 19:13:47 AEDT
**
** Edited by Tessa Song
** Student ID : 597952
** Thu 14 May 2015
**
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"



/*
** Create graph with number_of_vertices vertices
*/
Graph * graph_new(int number_of_vertices) {
    assert(number_of_vertices > 0);
    
    Graph *g = (Graph *)malloc(sizeof(Graph));
    assert(g);
    
    g->data = NULL;
    g->number_of_vertices = number_of_vertices;
    g->vertices = (Vertex *)malloc(sizeof(Vertex)*number_of_vertices);
    assert(g->vertices);
    
    // Put basic info to each vertex in this graph and allocate memory
    int i;
    for(i = 0;i<number_of_vertices;i++){
    	//shrink the possible number of edges for the large 'number_of_vertices'  
    	g->vertices[i].max_num_edges = number_of_vertices/1000+1;
    	g->vertices[i].edges = (Edge *)malloc(sizeof(Edge)*(number_of_vertices/1000+1));
    	assert(g->vertices[i].edges);
    	
    	g->vertices[i].num_edges = 0;
    	g->vertices[i].label = i; 
    	g->vertices[i].data = (void *)0;
    }
    
    return(g);
}



/*
** Add edge to g. 
*/
void graph_add_edge(Graph *g, Label v, Label u, int dist, void *data) {
    assert(g);
     
	// vectex range check    
    if( (v < 0 || v >= g->number_of_vertices) ||
    	(u < 0 || u >= g->number_of_vertices) ){
    	fprintf(stderr,"Vertex in incorrect range.\n");
    	exit(EXIT_FAILURE);
    }

    // if there are not enough space for new edge, realloc 
    if(g->vertices[v].num_edges == g->vertices[v].max_num_edges){
		g->vertices[v].edges = (Edge *)realloc(g->vertices[v].edges, 
				sizeof(Edge)*(g->vertices[v].max_num_edges)*2);
		assert(g->vertices[v].edges);
		g->vertices[v].max_num_edges = (g->vertices[v].max_num_edges)*2;

	}
	
	// Put the given info to the edge struct
	g->vertices[v].edges[g->vertices[v].num_edges].data = data;
	g->vertices[v].edges[g->vertices[v].num_edges].u = u;
	g->vertices[v].edges[g->vertices[v].num_edges].dist = dist;
	g->vertices[v].num_edges++;

}



/*
** Delete edge from g. Only deletes one copy if there are multiple.
** Does nothing if u is not in v's list.
*/
void graph_del_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);

    int num_edges = g->vertices[v].num_edges;
    int i = 0;
    
    while(i<num_edges){
    	if(g->vertices[v].edges[i].u == u){
    		// set this edge as deleted
    		g->vertices[v].edges[i].u = EDGE_DELETED;
    		break;
    	}
    	
    	i++;
    }
}



/*
** Return pointer to start of edge array for vertex v
** Set n to the number of items in the edge array.
*/
Edge * graph_get_edge_array(Graph *g, Label v, int *num_edges) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);

    *num_edges = g->vertices[v].num_edges;

    return g->vertices[v].edges;
}



/*
** Return 1 if (v,u) is in g
*/
int graph_has_edge(Graph *g, Label v, Label u) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    assert(u >= 0 && u < g->number_of_vertices);
    
    int num_edges = g->vertices[v].num_edges;
    int i;
    
    if(u==EDGE_DELETED)
    	return 0;
     
    for(i = 0;i<num_edges;i++){
    	if(g->vertices[v].edges[i].u == u)
    		return 1;
    }

    return 0;
}



/*
** Set vertex's data to data
*/
void graph_set_vertex_data(Graph *g, Label v, void *data) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    
    g->vertices[v].data = data;
}



/*
** Simple explore for calling from dfs that doesn't actually do anything.
** Use as a template for writing your own explore() functions.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted 
*/
void explore(Graph *g, Label v) {
    if (g->vertices[v].data)
        return;

    // mark as visited
    g->vertices[v].data = (void *)1; 

    for(int i = 0 ; i < g->vertices[v].num_edges ; i++)
       explore(g, g->vertices[v].edges[i].u);
}



/*
** Perform DFS beginning at v, calling pre() and post() as appropriate.
** ASSUMES vertex->data is 1 or 0 for visited and unvisted.
** Returns how many components there are.
*/
int graph_dfs(Graph *g, Label v) {
    assert(g);
    assert(v >= 0 && v < g->number_of_vertices);
    int comp = 0;
    
    // First explore from v
    explore(g, v);
    comp++;

    // Now do the rest (if any)
    for(int i = 0; i < g->number_of_vertices ; i++){
    	
    	if(g->vertices[i].data==0){
    		explore(g, i);
    		comp++;
    	}

    }
    
    return comp;
}



/*
** Free all the allocated memory
*/
void destroyGraph(Graph *g){
	int i;
    for(i = 0;i<g->number_of_vertices;i++){
    	free(g->vertices[i].edges);
    }
    
    free(g->vertices);
    free(g);
}
