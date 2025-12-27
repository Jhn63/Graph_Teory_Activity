#include <stdio.h>
#include <stdlib.h>
#include "v_list.h"

//constructor
v_list *new_vlist() {
    v_list *vl = (v_list*) malloc(sizeof(v_list));
    if (vl) {
        vl->head = NULL;
        vl->size = 0;
    }
    return vl;
}

//destructor
int destroy_vlist(v_list *list) {
    if (list->size) {
        vertex *current = list->head;
        vertex *c_next = current->next;
        while (current) {
            free(current);
            current = c_next;
            if (c_next) { 
                c_next = current->next; 
            }
        }
    }
    free(list);
    list = NULL;
    return 1;
}

vertex *new_vertex(int id) {
    vertex *v = (vertex*) malloc(sizeof(vertex));
    if (v) {
        v->id = id;
        v->next = NULL;
        v->reincidence = 1;
    }
    return v;
}

//insertion in the end
int add_vertex(v_list *list, int id) {
    if (!list || id < 0) { return 0; }
    vertex *item = new_vertex(id);

    if (!list->size) {
        list->head = item;

    } else {
        vertex *aux = list->head;
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = item;
    }
    list->size++;

    return 1;
}

//insertion without reapeted elements 
//could be better using hash function
int add_as_collection_vlist(v_list *list, int id) {
    if (!list) { return 0; }
    vertex *item = new_vertex(id);

    if (!list->size) {
        list->head = item;

    } else {
        vertex *current;
        vertex *aux = list->head;
        while (aux) {

            if (aux->id == item->id) {
                aux->reincidence++;
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

vertex *mid_point(vertex *head){
    vertex *slow = head;
    vertex *fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

vertex *merge(vertex *v1, vertex *v2) {
    if (!v1) { return v2; }
    if (!v2) { return v1; }

    vertex *aux;
    if (v1->id < v2->id) {
        aux = v1;
        aux->next = merge(v1->next, v2);

    } else {
        aux = v2;
        aux->next = merge(v2->next, v1);
    }
    return aux;
}

vertex *sort_vlist(vertex *head) {
    if (!head || !head->next) {
        return head;
    }

    vertex *aux1 = head;
    vertex *mid = mid_point(aux1);
    vertex *aux2 = mid->next;
    mid->next = NULL;

    aux1 = sort_vlist(aux1);
    aux2 = sort_vlist(aux2);

    return merge(aux1, aux2);
}

void print_vlist(v_list list) {
    vertex *aux = list.head;
    while (aux) {
        printf("%d -> ", aux->id);
        aux = aux->next;
    }
    printf("\n");
}