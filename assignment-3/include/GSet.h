//
// Created by Melissa on 04/10/2023.
//

#ifndef ATIVIDADE_3_GSET_H
#define ATIVIDADE_3_GSET_H


#include <utility>

class GSet {
public:
    int id;
    bool simple;
    GSet *set1, *set2;

    GSet(int vertex) : id(vertex), simple(true), set1(nullptr), set2(nullptr) {};
    GSet(int id, GSet *set1, GSet *set2) : id(id), simple(false), set1(set1), set2(set2) {};

    bool operator==(const GSet &set) const;
    bool operator!=(const GSet &set) const;

    void copy(const GSet &gset);
};


#endif //ATIVIDADE_3_GSET_H
