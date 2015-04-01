//
// Created by Marcus on 4/1/2015.
//

#include "SemanticsHash.h"

size_t SemanticsHash::operator()(const Semantics &semantics) const {
    return hash<string>()(semantics.semName);
}
