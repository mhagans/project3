//
// Created by Marcus on 4/1/2015.
//

#include "Semantics.h"

using namespace std;

Semantics::Semantics(string ID, string Type, string Name, int Depth) {
    semID = ID;
    semType = Type;
    semName = Name;
    semDepth = Depth;

}

bool Semantics::operator==(const Semantics &semantics) const {
    return semName == semantics.semID;
}
