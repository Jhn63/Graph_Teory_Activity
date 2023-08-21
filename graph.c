#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//constructor
graph *new_graph(int N, short **matrix) {
    graph *ppr = (graph*) malloc(sizeof(graph));
    if (!ppr) { return NULL; }
    
    ppr->n_vertex = N;
    ppr->matrix = matrix;
    ppr->list = (v_list**) malloc(N * sizeof(v_list*));
    for (int i = 0; i < ppr->n_vertex; i++) {
        ppr->list[i] = new_vlist();
    }

    int M = 0;
    for (int i = 0; i < ppr->n_vertex; i++) {
        for (int j = 0; j < ppr->n_vertex; j++) {
            
            if (ppr->matrix[i][j] == 1) {
                add_vertex(ppr->list[i], j);
                M++;
            }

        }
    }
    ppr->m_edges = M/2;
    return ppr;
}

int destroy_graph(graph *g) {
    for (int i = 0; i < g->n_vertex; i++) {
        destroy_vlist(g->list[i]);
    }
    free(g->matrix);
    free(g);
    g = NULL;
    return 1;
}

int max_degree(graph copy) {
    v_list *aux = copy.list[0];
    int max = aux->size;

    for (int i = 1; i < copy.n_vertex; i++) {
        aux = copy.list[i];
        if (aux->size > max) {
            max = aux->size;
        }
    }
    return max;
}

int min_degree(graph copy) {
    v_list *aux = copy.list[0];
    int min = aux->size;
    
    for (int i = 1; i < copy.n_vertex; i++) {
        aux = copy.list[i];
        if (aux->size < min) {
            min = aux->size;
        }
    }
    return min;
}

int vertex_degree(graph copy, int vertex_id) {
    v_list *ll = copy.list[vertex_id];
    return ll->size;
}

v_list *degree_sequel(graph copy) {
    v_list *ll = new_vlist();
    for (int i = 0; i < copy.n_vertex; i++) {
        v_list *aux = copy.list[i];
        add_as_collection_vlist(ll, aux->size);
    }
    ll->head = sort_vlist(ll->head);
    return ll;
}

v_list *open_neighborhood(graph copy, int vertex_id) {
    v_list *ll = copy.list[vertex_id];
    ll->head = sort_vlist(ll->head);
    return ll;
}

v_list *close_neighborhood(graph copy, int vertex_id) {
    v_list *ll = copy.list[vertex_id];
    add_vertex(ll, vertex_id);
    ll->head = sort_vlist(ll->head);
    return ll;
}

int is_neighbor(graph copy, int vertex_id1, int vertex_id2) {
    return copy.matrix[vertex_id1][vertex_id2];
}

int is_regular(graph copy) {
    int k = copy.list[0]->size;
    for (int i = 1; i < copy.n_vertex; i++) {
        if ( copy.list[i]->size != k ) {
            k = -1;     break;
        }
    }
    return k;
}

int is_complete(graph copy) {
    int N = (copy.n_vertex * (copy.n_vertex -1)) / 2;
    return N == copy.m_edges;
}

v_list *universal_vertexes(graph copy) {
    v_list *ll = new_vlist();
    for (int i = 0; i < copy.n_vertex; i++) {
        v_list *aux = copy.list[i];
        if (aux->size == copy.n_vertex-1) {
            add_vertex(ll, i);
        }
    }
    return ll;
}

v_list *isoleted_vertexes(graph copy) {
    v_list *ll = new_vlist();
    for (int i = 0; i < copy.n_vertex; i++) {
        v_list *aux = copy.list[i];
        if (!aux->size) {   //list size 0
            add_vertex(ll, i);
        }
    }
    return ll;   
}

int is_subgraph(graph copy, v_list vertexes, e_list edges) {
    vertex *ver = vertexes.head;
    while (ver) {
        if (ver->id > copy.n_vertex-1) {
            return 0;
        }
        ver = ver->next;
    }
    
    edge *edg = edges.head;
    while (edg) {
        int i = edg->i;
        int j = edg->j;
        if (!copy.matrix[i][j]) {
            return 0;
        }
        edg = edg->next;
    }

    return 1;
}
 
int is_passing(graph copy, v_list list) {
    vertex *current = list.head;
    vertex *c_next = current->next;
    while (c_next) {
        if (!is_neighbor(copy,current->id, c_next->id)) {
            return 0;
        }
        current = current->next;
        c_next = current->next;
    }
    return 1;
}

//not the best implementention could be better
int is_path(graph copy, v_list list) {
    v_list *ll = new_vlist();
    
    vertex *aux = list.head;
    while (aux) {
        if (!add_as_collection_vlist(ll, aux->id)) {
            destroy_vlist(ll); //to test
            return 0;
        }
        aux = aux->next;
    }
    destroy_vlist(ll); //to test
    return 1;
}

int is_cicle(graph copy, v_list list) {
    v_list *ll = new_vlist();
    vertex *aux = list.head;

    int first = aux->id;
    int last = first;
    while (aux) {
        if (!aux->next) {
            last = aux->id;
            break;
        }

        if (!add_as_collection_vlist(ll, aux->id)) {
            destroy_vlist(ll); //to test
            return 0;
        }
        aux = aux->next;
    }

    destroy_vlist(ll); //to test
    if (first != last) {
        return 0;
    }
    return 1;   
}

int is_trail(graph copy, v_list list) {
    e_list *ll = new_elist();
    
    vertex *current = list.head;
    vertex *c_next = current->next;
    while (c_next) {
        int i = current->id;
        int j = c_next->id;
        if (!add_as_collection_elist(ll, i, j)) {
            destroy_elist(ll); //to test
            return 0;
        }
        current = current->next;
        c_next = current->next;
    }
    destroy_elist(ll); //to test
    return 1;
}

int is_clique(graph copy, v_list list) {
    vertex *current = list.head;
    
    while (current) {
        vertex *aux = current->next;
        while (aux) {
            if (!is_neighbor(copy, current->id, aux->id)) {
                return 0;
            }
            aux = aux->next;
        }
        current = current->next;
    }
    return 1;
}

int is_max_clique(graph copy, v_list list) {
    v_list *reincidence_list = new_vlist();
    
    vertex *current = list.head;
    while (current) {
        v_list *nh = open_neighborhood(copy, current->id);
        vertex *aux1 = nh->head;
        while (aux1) {
            
            int is_fine = 1; // verificando se aux1 já é um vertice do clique
            for (vertex *aux2 = list.head; aux2 ; aux2 = aux2->next ) {
                if (aux1->id == aux2->id) {
                    is_fine = 0;
                    break;
                }
            }
            if (is_fine) {
                add_as_collection_vlist(reincidence_list, aux1->id); // o vertice não faz parte do clique e pode ser adicionado
            }

            aux1 = aux1->next;
        }
        free(nh);
        current = current->next;
    }
    
    //Se um vertice for reincidente em até o tamanho do clique, então
    //esse vertice contem arestas capazes de aumentar o clique, logo não é maximal
    for (vertex *aux = reincidence_list->head; aux ; aux = aux->next ) {
        if (aux->reincidence == list.size) {
            free(reincidence_list);
            return 0;
        }
    }
    free(reincidence_list);
    return 1;
}

int is_independent(graph copy, v_list list) {
    vertex *current = list.head;
    while (current) {

        vertex *aux = current->next;
        while (aux) {
            if (is_neighbor(copy, current->id, aux->id)) {
                return 0;
            }
            aux = aux->next;
        }

        current = current->next;
    }
    return 1;
}

graph *complement(graph copy) {
    int N = copy.n_vertex;
    short **matriz = (short**) malloc(N * sizeof(short*));
    for (int i = 0; i < N; i++) {
        matriz[i] = (short*) malloc(N * sizeof(short));
    }

    for (int i = 0; i < N; i++ ) {
        for (int j = 0; j < N; j++ ) {

            if (i == j) {
                matriz[i][j] = 0;
            }
            else if (copy.matrix[i][j]) {
                matriz[i][j] = 0;    
            }
            else { 
                matriz[i][j] = 1; 
            }
        }   
    }
    graph *comp = new_graph(N, matriz);
    return comp;
}

void print_graph1(graph copy) {
    for (int i = 0; i < copy.n_vertex; i++) {
        for (int j = 0; j < copy.n_vertex; j++) {
            printf("%d ", copy.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_graph2(graph copy) {
    for (int i = 0; i < copy.n_vertex; i++) {
        v_list *ll = copy.list[i];
        printf("[%d]: ", i);
        print_vlist(*ll);
    }
}