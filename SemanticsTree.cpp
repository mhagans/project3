//
// Created by Marcus on 4/1/2015.
//

#include <algorithm>
#include "SemanticsTree.h"
#include <string>
#include <iostream>

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
        root->parentNode = "";
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
            leaf->numberOfParams=0;
            leaf->left->left = NULL;
            leaf->left->right = NULL;
        }
    }else {

        if(key.compare(leaf->key) > 0 || key.compare(leaf->key) == 0) {
            if(leaf->right != NULL) {
                insert(key, leaf->right);
            }else {
                leaf->right=new node;
                leaf->numberOfParams= 0;
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
    currentNode->numberOfParams++;


}

bool SemanticsTree::isCreated() {
    if(root == NULL) {
        return false;
    }
    return true;
}

bool SemanticsTree::isMainCreated() {
    node * isMain = root;
    while (isMain != NULL) {
        if (isMain->key.compare("main") == 0) {
            return true;
        }else {
            isMain = isMain->left == NULL ? isMain->right : isMain->left;
        }
    }

    return false;
}

void SemanticsTree::insert(string key, string type) {
    if(root!=NULL)
        insert(key, type, root);
    else
    {
        root = new node;
        root->key = key;
        root->semType = type;
        root->parentNode = "";
        root->left=NULL;
        root->right=NULL;
    }
}
void SemanticsTree::insert(string key, string type, node *leaf) {

    if(key.compare(leaf->key) < 0 ) {
        if(leaf->left != NULL) {
            insert(key, type, leaf->left);
        }else {
            if (isMainCreated()) {
                cout << "REJECT" << endl;
                exit(1);
            }
            leaf->left = new node;
            leaf->left->key = key;
            leaf->left->semType = type;
            leaf->numberOfParams=0;
            leaf->left->hasReturn = false;
            leaf->left->left = NULL;
            leaf->left->right = NULL;

        }
    }else {

        if(key.compare(leaf->key) > 0 || key.compare(leaf->key) == 0) {
            if(leaf->right != NULL) {
                insert(key, type, leaf->right);
            }else {
                if (isMainCreated()) {
                    cout << "REJECT" << endl;
                    exit(1);
                }
                leaf->right=new node;
                leaf->numberOfParams= 0;
                leaf->right->key = key;
                leaf->right->semType = type;
                leaf->right->hasReturn = false;
                leaf->right->left=NULL;
                leaf->right->right=NULL;

            }

        }
    }
}


bool SemanticsTree::hasReturn(string key) {
    node *returnNode = search(key);
    if(!returnNode->hasReturn) {
        cout << "REJECT" << endl;
        exit(1);
    }
    return false;
}

string SemanticsTree::hasBeenDeclared(string id) {
    bool isDeclared = false;
    string type;
    node* returnNode = new node;
    returnNode = root;
    while (returnNode != NULL && !isDeclared) {
        for (vector<varList>::iterator it = returnNode->variables.begin(); it != returnNode->variables.end(); ++it) {
            if(it->varID.compare(id) == 0) {
                isDeclared = true;
                type = it->varType;
                break;
            }
        }
        if(returnNode->right != NULL) {
            returnNode = returnNode->right;
        } else {
            returnNode = returnNode->left;
        }

    }
    if (isDeclared) {
        return type;
    } else {
        return "";
    }

}
