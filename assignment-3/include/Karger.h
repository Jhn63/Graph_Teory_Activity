//
// Created by Jhn on 12/10/2023.
//

#ifndef ATIVIDADE_3_KARGER_H
#define ATIVIDADE_3_KARGER_H

#include "SuperGraph.h"

class Karger {
private:
    SuperGraph *s_graph;

public:
    Karger(SuperGraph *s);

    std::vector<std::pair<int,int>> min_cut();
};


#endif //ATIVIDADE_3_KARGER_H
