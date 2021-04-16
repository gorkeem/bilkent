#ifndef NGRAM_H_INCLUDED
#define NGRAM_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "PbBSTNode.h"
using namespace std;


class NgramTree{
public:
    //constructors
    NgramTree();
    NgramTree(const NgramTree &tree);

    //destructor
    ~NgramTree();

    // homework functions
    void addNgram(string ngram);
    int getTotalNgramCount();
    bool isFull();
    bool isComplete();
    void generateTree(string filename, int n); 

    // helper functions
    void getTotalNgramCountHelper(TreeNode *&treePtr, int &cnt);
    void generateTreeHelper(string token, int n);
    ostream& print( ostream& out ) const;
    ostream& printHelper( ostream& out, TreeNode* root ) const;
    bool isCompleteHelper(TreeNode *&root, int index, int nodeCount);

    // all binary search tree functions
    bool isEmpty() const;
    void searchTreeInsert(const string &newItem);
    void insertKey(string key);
    int getHeight();
    int doHeight(TreeNode *&treePtr);
    int getNodeCount();
    int findNodesRequired();

protected:
    void insertItem(TreeNode *&treePtr, const string& item);

private:
    TreeNode *root;
    int nodeCounter;

    // Homework function
    friend ostream& operator<<(ostream& out, NgramTree &tree);
friend class TreeNode;
};

#endif // PBBST_H_INCLUDED