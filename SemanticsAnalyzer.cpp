//
// Created by Marcus on 3/29/2015.
//

#include "SemanticsAnalyzer.h"

SemanticsAnalyzer::SemanticsAnalyzer(string type, string id) {
    semType = type;
    semId = id;
    myString = "The type: " + semType + " The id: " + semId;

}


string SemanticsAnalyzer::toString() {
    return myString;
}
