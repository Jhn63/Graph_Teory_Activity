//
// Created by Jhn on 04/10/2023.
//

#ifndef ATIVIDADE_3_SUPERGRAPH_H
#define ATIVIDADE_3_SUPERGRAPH_H

#include <ctime>
#include <random>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include "GSet.h"

struct hash_pair {
    size_t operator()(const std::pair<int,int> &p) const {
        return (p.first * p.second) * 33;
    }
};

class SuperGraph {
private:
    int max_set;
    std::unordered_map<int, GSet> *vertex;
    std::vector<std::vector<uint8_t>> *matrix;
    std::unordered_set<std::pair<int, int>, hash_pair> *edges;

    void initialize();
    void contract(int v, int u);
    std::vector<std::pair<int,int>> refine(std::vector<std::pair<GSet,GSet>> bt_list);
public:
    SuperGraph(std::vector<std::vector<uint8_t>> *m);
    ~SuperGraph();

    void make_set(int v); // create a new set and push into it
    void make_pair(int v, int u) const; //insert edges into it (v < u)
    void merge(int v, int u);

    void clear();
    int vtx_total();
    std::pair<int,int> get_random_pair();
    std::vector<std::pair<int,int>> back_tracking();
};

#endif //ATIVIDADE_3_SUPERGRAPH_H
