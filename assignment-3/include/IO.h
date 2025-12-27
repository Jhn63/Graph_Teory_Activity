//
// Created by Jhn on 02/11/2023.
//

#ifndef ATIVIDADE_3_IO_H
#define ATIVIDADE_3_IO_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class IO {
public:
    std::vector<std::vector<uint8_t>> *load_data(std::string path);
};


#endif //ATIVIDADE_3_IO_H
