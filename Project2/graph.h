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

#define EDGE_DELETED -1

typedef int Label;   // a vertex label (should be numeric to index edge lists)

typedef struct {
    void   *data;   // any data you want to store about an edge
    Label u;        // end vertex of edge
    int dist;
} Edge;

typedef struct {
    void   *data;        // any data you want to store about a vertex
    Label  label;        // this vertex's label
    Edge  *edges;        // array of edges [0..num_edges-1]
    int   num_edges;     // number of edges
    int   max_num_edges; // current malloced size of edges array,
    					 //   num_edges <= max_num_edges
} Vertex;

typedef struct {
    void   *data;              // any data you want to store about a graph
    int    number_of_vertices; // |V|
    Vertex *vertices;          // array of vertices [0..number_of_vertices-1]
} Graph;


// prototypes
Graph *graph_new(int number_of_vertices);
void  graph_add_edge(Graph *g, Label v, Label u, int dist, void *data);
void  graph_del_edge(Graph *g, Label v, Label u);   
int   graph_has_edge(Graph *g, Label v, Label u);
Edge *graph_get_edge_array(Graph *g, Label v, int *num_edges);
void  graph_set_vertex_data(Graph *g, Label v, void *data);
void explore(Graph *g, Label v);
int graph_dfs(Graph *g, Label v);
void destroyGraph(Graph *g);
