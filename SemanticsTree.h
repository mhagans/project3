//
// Created by Marcus on 4/1/2015.
//

#ifndef PROJECT3_SEMANTICSTREE_H
#define PROJECT3_SEMANTICSTREE_H

#include <string>

using namespace std;
struct node{
    string semID;
    string semType;
    int depth;
    bool function;
    node *left;
    node *right;
};

class SemanticsTree {
public:
    SemanticsTree();
    ~SemanticsTree();

    void insert(string key, string type);
    node *search(string key);
    void destroy_tree();

private:
    void destroy_tree(node *leaf);

    void insert(string key, string type, node *leaf);
    node *search(string key, node *leaf);

    node *root;

};


#endif //PROJECT3_SEMANTICSTREE_H
