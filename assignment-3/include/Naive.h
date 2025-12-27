//
// Created by Jhn on 01/11/2023.
//

#ifndef ATIVIDADE_3_NAIVE_H
#define ATIVIDADE_3_NAIVE_H

#include <set>
#include <map>
#include <list>
#include <queue>
#include <ctime>
#include <vector>
#include <random>
#include <cstdint>
#include <algorithm>

class Naive {
private:
    std::vector<int> red;
    std::vector<int> blue;
    std::vector<uint8_t> *vertex;
    std::vector<std::vector<uint8_t>> *matrix;

    std::vector<std::list<int>> *list;

    void make_set();
    bool is_connected_subgraph(std::vector<int> ver);

public:
    Naive(std::vector<std::vector<uint8_t>> *m);
    ~Naive();

    void clear();
    std::vector<std::pair<int,int>> min_cut();
};


#endif //ATIVIDADE_3_NAIVE_H
