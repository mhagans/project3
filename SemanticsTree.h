//
// Created by Marcus on 4/1/2015.
//

#ifndef PROJECT3_SEMANTICSTREE_H
#define PROJECT3_SEMANTICSTREE_H

#include <string>
#include <unordered_map>
#include <string>

using namespace std;

struct varList{
    string varID;
    string varType;
    int value;
};

struct funList{
    string funID;
    string funType;
    vector<varList> funVariables;
    vector<varList> funParams;

};
struct node{
    string semID;
    string semType;
    string key;
    node *left;
    node *right;
    int numberOfParams;
    string parentNode;
    vector<varList> variables;
    vector<funList> functions;
};


class SemanticsTree {

public:

    SemanticsTree();
    ~SemanticsTree();

    void insert(string key);
    node *search(string key);
    void destroy_tree();
    void varInsert(string key, string id, string type);
    bool isCreated();

private:
    void destroy_tree(node *leaf);
    void varInsert(string key, string id, string type, node *leaf);
    void insert(string key,node *leaf);
    node *search(string key, node *leaf);

    node *root;
    node *currentNode;
    varList *vari;
    funList *fun;

};

#endif //PROJECT3_SEMANTICSTREE_H
