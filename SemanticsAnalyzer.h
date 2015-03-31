//
// Created by Marcus on 3/29/2015.
//
#include "LexicalAnalyzer.hpp"

#ifndef PROJECT3_SEMANTICSANALYZER_H
#define PROJECT3_SEMANTICSANALYZER_H


class SemanticsAnalyzer {

public:
    string semType;
    string semId;
    string myString;
    string toString();

    SemanticsAnalyzer(string type, string id);

};



#endif //PROJECT3_SEMANTICSANALYZER_H
