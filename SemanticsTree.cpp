//
// Created by Marcus on 4/1/2015.
//

#include <algorithm>
#include "SemanticsTree.h"
#include <string>

SemanticsTree::SemanticsTree() {
    root = NULL;
}

SemanticsTree::~SemanticsTree() {
    destroy_tree();
}

void SemanticsTree::insert(string key, string type) {
    if(root!=NULL)
        insert(key, type, root);
    else
    {
        root = new node;
        root->semID = key;
        root->semType = type;
        root->left=NULL;
        root->right=NULL;
    }
}


void SemanticsTree::destroy_tree() {
    destroy_tree(root);
}

void SemanticsTree::destroy_tree(node *leaf) {
    if(leaf != NULL) {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf;
    }
}

void SemanticsTree::insert(string key, string type,  node *leaf) {
    int comparecheck = key.compare(leaf->semID);
    if(key.compare(leaf->semID) < 0 ) {
        if(leaf->left != NULL) {
            insert(key, type, leaf->left);
        }else {
            leaf->left = new node;
            leaf->left->semID = key;
            leaf->left->semType = type;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }else {
        int comparecheck2 = key.compare(leaf->semID);
        if(key.compare(leaf->semID) > 0 || key.compare(leaf->semID) == 0) {
            if(leaf->right != NULL) {
                insert(key, type, leaf->right);
            }else {
                leaf->right=new node;
                leaf->right->semID = key;
                leaf->right->semType = type;
                leaf->right->left=NULL;
                leaf->right->right=NULL;
            }

        }
    }
}

node *SemanticsTree::search(string key, node *leaf) {
    if(leaf!=NULL)
    {
        if(key.compare(leaf->semID) == 0 )
            return leaf;
        if(key.compare(leaf->semID) <0)
            return search(key, leaf->left);
        else
            return search(key, leaf->right);
    }
    else return NULL;
}

node *SemanticsTree::search(string key) {
    return search(key, root);
}
