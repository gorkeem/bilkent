#ifndef PBBSTNODE_H_INCLUDED
#define PBBSTNODE_H_INCLUDED
#include <iostream>
#include <stdio.h>
using namespace std;

class TreeNode{            // node in the tree

private:
    TreeNode(){}
    TreeNode(const string &nodeItem,
        TreeNode *left = NULL,
        TreeNode *right = NULL,
        int counter=0)
        :item(nodeItem), leftChildPtr(left), rightChildPtr(right), count(counter){}

    string item;      // data portion
    TreeNode *leftChildPtr;  // pointer to left child
    TreeNode *rightChildPtr; // pointer to right child
    int count;

    friend class NgramTree;
};
#endif // PBBSTNODE_H_INCLUDED
