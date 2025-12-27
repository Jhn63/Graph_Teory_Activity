//
// Created by Jhn on 01/11/2023.
//

#include <iostream>
#include "../include/Naive.h"

Naive::Naive(std::vector<std::vector<uint8_t>> *m) : matrix(m) {
    srand(time(NULL));
    this->vertex = new std::vector<uint8_t>(m->size());
    this->list = new std::vector<std::list<int>>(m->size());

    int row = 0;
    for (auto i = m->begin(); i != m->end(); i++, row++) {

        int column = 0;
        for (auto j = i->begin(); j != i->end(); j++, column++) {
            if (*j == 1) {
                auto it = list->begin() + row;
                it->push_back(column);
            }
        }
    }
}

Naive::~Naive() {
    delete vertex;
    delete matrix;
}

void Naive::make_set() {
    bool flag1 = true, flag2 = true;
    while (flag1 or flag2) {

        int gen = fabs(rand() % (vertex->size() - 2));

        auto aux = vertex->begin();
        for ( ;aux != vertex->end(); aux++) {
            *aux = false;
        }

        red.clear(); blue.clear();

        for (int i = 0; i < gen; ) {
            int num = fabs(rand() % (vertex->size() - 1));

            auto v = vertex->at(num);
            if (v == false) {
                vertex->at(num) = true;
                red.push_back(num);
                i++;
            }
        }
        if (is_connected_subgraph(red)) { flag1 = false; }


        auto it = vertex->begin();
        for (int i = 0; it != vertex->end(); i++, it++) {

            if (*it == false) {
                *it = true;
                blue.push_back(i);
            }
        }
        if (is_connected_subgraph(blue)) { flag2 = false; }
    }
}

bool Naive::is_connected_subgraph(std::vector<int> ver) {
    if (ver.size() == 0) { return false; }

    std::queue<int> fifo;
    fifo.push(*ver.begin());

    std::map<int,int> visited;
    for (auto e : ver) {
        visited[e] = 0;
    }
    visited[*ver.begin()] = 1;

    int count = 1;
    while (!fifo.empty()) {
        int v = fifo.front();
        fifo.pop();

        auto l = list->begin() + v;
        std::list<int>::iterator it = l->begin();
        for ( ; it != l->end(); it++) {

            auto inst = visited.find(*it);
            if (inst != visited.end() and inst->second == 0) {
                visited[*it] = 1;
                fifo.push(*it);
                count++;
            }
        }

    }
    return ver.size() == count;
}

std::vector<std::pair<int,int>> Naive::min_cut() {
    make_set();
    std::set<std::pair<int,int>> conj;

    auto row = matrix->begin()+1;
    for (int v = 1 ; row != matrix->end(); v++, row++) {

        auto cell = row->begin();
        for (int w = 0; cell != row->begin()+v+1; w++, cell++) {

            if(*cell == 1) {
                auto e1 = std::find(red.begin(), red.end(), v);
                auto e2 = std::find(red.begin(), red.end(), w);
                if (e1 == red.end() xor e2 == red.end()) {
                    if ( v > w ) {
                        conj.insert({w,v});
                    }
                    else {
                        conj.insert({v,w});
                    }
                }
            }
        }
    }
    std::vector<std::pair<int,int>> edges(conj.begin(), conj.end());
    return edges;
}