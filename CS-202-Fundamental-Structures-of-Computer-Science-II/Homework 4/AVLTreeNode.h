
#ifndef AVLTREENODE_H_INCLUDED
#define AVLTREENODE_H_INCLUDED

#include <iostream>
#include <stdio.h>
using namespace std;

class TreeNode{            // node in the tree

private:
    TreeNode(){}
    TreeNode(const string &nodeItem,
        TreeNode *left = NULL,
        TreeNode *right = NULL)
        :item(nodeItem), left(left), right(right){
            height = 1;
            count = 1;
        }

    string item;       // data portion
    int count;
    int height;
    TreeNode *left;  // pointer to left child
    TreeNode *right; // pointer to right child


    friend class AVLTree;
};
#endif // AVLTREENODE_H_INCLUDED
