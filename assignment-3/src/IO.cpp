//
// Created by Jhn on 02/11/2023.
//

#include "../include/IO.h"

std::vector<std::vector<uint8_t>> *IO::load_data(std::string path) {
    auto *matrix = new std::vector<std::vector<uint8_t>>;

    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        std::cerr << "file not open";
        delete this;  exit(-1);
    }

    int trash; input >> trash;

    std::string line;
    while (!input.eof()) {
        std::getline(input, line);

        int data;
        if (!line.empty()) {
            std::vector<uint8_t> row;
            std::istringstream stream(line);
            while (stream >> data) {
                row.push_back(data);
            }
            matrix->push_back(row);
        }
    }
    input.close();
    return matrix;
}