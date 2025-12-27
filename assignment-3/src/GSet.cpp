//
// Created by Melissa on 04/10/2023.
//

#include "../include/GSet.h"

bool GSet::operator==(const GSet &set) const {
    return this->id == set.id;
}

bool GSet::operator!=(const GSet &set) const {
    return this->id != set.id;
}

void GSet::copy(const GSet &gset) {
    this->id = gset.id;
    this->set1 = gset.set1;
    this->set2 = gset.set2;
    this->simple = gset.simple;
}
