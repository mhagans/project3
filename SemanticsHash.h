//
// Created by Marcus on 4/1/2015.
//

#ifndef PROJECT3_SEMANTICSHASH_H
#define PROJECT3_SEMANTICSHASH_H

#include "Semantics.h"

class SemanticsHash {
public:
    size_t  operator()(const Semantics &semantics) const;
};


#endif //PROJECT3_SEMANTICSHASH_H
