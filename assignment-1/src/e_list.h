#ifndef E_LIST_H_
#define E_LIST_H_

/* List of edges.
** Struct edge keep the id of the two vertices connected by it */

typedef struct e_list {
    int size;
    struct edge *head;
} e_list;

typedef struct edge {
    int i, j;
    struct edge *next;
} edge;

//constructors
edge *new_edge(int i, int j);
e_list *new_elist();

//destructor
int destroy_elist(e_list *list);

//list methods
int add_edge(e_list *list, int i, int j);
int add_as_collection_elist(e_list *list, int i, int j);

#endif