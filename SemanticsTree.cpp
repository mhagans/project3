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

void SemanticsTree::insert(string key) {
    if(root!=NULL)
        insert(key, root);
    else
    {
        root = new node;
        root->key = key;
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

void SemanticsTree::insert(string key, node *leaf) {

    if(key.compare(leaf->key) < 0 ) {
        if(leaf->left != NULL) {
            insert(key, leaf->left);
        }else {
            leaf->left = new node;
            leaf->left->key = key;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }else {

        if(key.compare(leaf->key) > 0 || key.compare(leaf->key) == 0) {
            if(leaf->right != NULL) {
                insert(key, leaf->right);
            }else {
                leaf->right=new node;
                leaf->right->key = key;
                leaf->right->left=NULL;
                leaf->right->right=NULL;
            }

        }
    }
}

node *SemanticsTree::search(string key, node *leaf) {
    if(leaf!=NULL)
    {
        if(key.compare(leaf->key) == 0 )
            return leaf;
        if(key.compare(leaf->key) <0)
            return search(key, leaf->left);
        else
            return search(key, leaf->right);
    }
    else return NULL;
}

node *SemanticsTree::search(string key) {
    return search(key, root);
}

void SemanticsTree::varInsert(string key, string id, string type) {
    currentNode = search(key, root);
    varInsert(key, id, type, currentNode);

}

void SemanticsTree::varInsert(string key, string id, string type, node *leaf) {
    vari = new varList;
    vari->varID = id;
    vari->varType = type;
    leaf->variables.push_back(*vari);

}

bool SemanticsTree::isCreated() {
    if(root == NULL) {
        return false;
    }
    return true;
}
