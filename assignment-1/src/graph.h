#ifndef GRAPH_H_
#define GRAPH_H_
#include "v_list.h"
#include "e_list.h"

typedef struct graph {
    int m_edges;
    int n_vertex;
    short **matrix;
    v_list **list; //array of list
} graph;

//constructor
graph *new_graph(int N, short **matrix);

//destructor
int destroy_graph(graph *g);

//methods
int max_degree(graph copy); // return the longest or shortest list's size, or even
int min_degree(graph copy); // interate through the matrix counting the number of elements in each line

v_list *degree_sequel(graph copy); //return a list of the each list's size

int vertex_degree(graph copy, int vertex_id); //return the list's size

v_list *open_neighborhood(graph copy, int vertex_id);  // return a list with each vertex's id close to the studied vertex
v_list *close_neighborhood(graph copy, int vertex_id); // the same function including the analyzing vertex's id

int is_neighbor(graph copy, int vertex_id1, int vertex_id2); // just verify in the matrix if it exist "connection" on cell [id1][id2]

int is_regular(graph copy); // verify if each list has the same size, in succesful matters return the size otherwise return -1s

int is_complete(graph copy); // use the function n(n-1)/2, in wich n is the number of vertex, and see if it matches with the number of edges

v_list *universal_vertexes(graph copy); //return a list containing the index of all list the have size equals to n-1, NULL if don't have any
v_list *isoleted_vertexes(graph copy); //return a list containing the index off all list size 0, NULL if do not find any

int is_subgraph(graph copy, v_list vertexes, e_list edges); //look if the id of each vertex is within the amount of vertexes, then
                                                            //look in the matrix if has connection on cells informed by the list of edges

int is_passing(graph copy, v_list list); // verify if the vertexes from the list is connected on sequel, use the the id of each element and the next one
                                        // to indentify if they represent a match in the 2d array

int is_path(graph copy, v_list list); // similar to is_passing function, but gotta make sure it don't reapeat elements

int is_cicle(graph copy, v_list list); // similar to is_path, just save the first id to verify if matches with last

int is_trail(graph copy, v_list list); // create a list of edges. anytime the program go through an edge, compare it to the others on the list, 
                                        //  then add then to the list, the function will return false if some element is reapeted

int is_clique(graph copy, v_list list); // to be a clique every elements need be neighbor to the others, verify it 

int is_max_clique(graph copy, v_list list);

int is_independent(graph copy, v_list list); // check if the elements are not in the neighborhood of each other 

graph *complement(graph copy);

void print_graph1(graph copy);

void print_graph2(graph copy);

#endif