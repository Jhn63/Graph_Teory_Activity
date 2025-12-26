#include <stdlib.h>
#include "e_list.h"

//constructor
e_list *new_elist() {
    e_list *el = (e_list*) malloc(sizeof(e_list));
    if (el) {
        el->head = NULL;
        el->size = 0;
    }
    return el;
}

//descrutctor
int destroy_elist(e_list *list) {
    edge *current = list->head;
    edge *c_next = current->next;
    while (current) {
        free(current);
        current = c_next;
        if (c_next) { 
            c_next = current->next; 
        }
    }
    free(list);
    list = NULL;
    return 1;
}

edge *new_edge(int i, int j) {
    edge *e = (edge*) malloc(sizeof(edge));
    if (e) {
        e->i = i;
        e->j = j;
        e->next = NULL;
    }
    return e;
}

int add_edge(e_list *list, int i, int j) {
    if (!list || i < 0 || j < 0) { return 0; }
    edge *item = new_edge(i, j);

    if (!list->size) {
        list->head = item;

    } else {
        edge *aux = list->head;
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = item;
    }
    list->size++;

    return 1;
}

int add_as_collection_elist(e_list *list, int i, int j) {
    if (!list || i < 0 || j < 0) { return 0; }
    edge *item = new_edge(i, j);

    if (!list->size) {
        list->head = item;

    } else {
        edge *current;
        edge *aux = list->head;
        while (aux) {

            if (aux->i == item->i && aux->j == item->j) {
                free(item); return 0;
            }
            if (aux->i == item->j && aux->j == item->i) {
                free(item); return 0;
            }
            current = aux;
            aux = aux->next;
        }
        current->next = item;
    }
    list->size++;

    return 1;
}