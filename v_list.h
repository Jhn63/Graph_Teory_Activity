#ifndef V_LIST_H_
#define V_LIST_H_

typedef struct v_list {
    int size;
    struct vertex *head;
} v_list;

typedef struct vertex {
    int id;
    struct vertex *next;
} vertex;

//constructors
vertex *new_vertex(int id);
v_list *new_vlist();

//destructor
int destroy_vlist(v_list *list);

//list methods
int add_vertex(v_list *list, int id);
int add_as_collection_vlist(v_list *list, int id); //add method wich don't allow reapeted elements

//merge sort algorithm
vertex *mid_point(vertex *head);
vertex *merge(vertex *v1, vertex *v2);
vertex *sort_vlist(vertex *head);

void print_vlist(v_list list);

#endif