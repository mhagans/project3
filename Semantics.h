//
// Created by Marcus on 4/1/2015.
//

#ifndef PROJECT3_SEMANTICS_H
#define PROJECT3_SEMANTICS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Semantics {
    string semID;
    string semType;
    int semDepth;
public:
    Semantics(string ID, string Type, string Name, int Depth);
    bool operator ==(const Semantics &semantics)const;
    string semName;
    vector<string> varList;
private:

};


#endif //PROJECT3_SEMANTICS_H
