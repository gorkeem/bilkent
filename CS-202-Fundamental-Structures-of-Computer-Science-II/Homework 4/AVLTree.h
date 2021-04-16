#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <cstdlib>
using namespace std;
#include "AVLTreeNode.h"


class AVLTree{
public:
    //constructors
    AVLTree();
    AVLTree(const AVLTree &tree);

    //destructor
    ~AVLTree();

    // AVL Tree Functions
    int getHeight(TreeNode *&treePtr);
    void singleLeftRotation(TreeNode *&treePtr);
    void singleRightRotation(TreeNode *&treePtr);
    void doubleLeftRightRotation(TreeNode *&treePtr);
    void doubleRightLeftRotation(TreeNode *&treePtr);
    int getBalance(TreeNode *&treePtr);
    void insertItem(TreeNode *&treePtr, const string& item);

    // Homework Functions
    void addWord(string key);
    void printHeight(ofstream &file);
    void printTotalWordCount(ofstream &file);
    void printTotalWordCountHelper(TreeNode *&treePtr, int &totalCount);
    void printWordFrequencies();
    void printWordFrequenciesHelper(TreeNode *&treePtr, ofstream &file);
    void printMostFrequent(ofstream &file);
    void printMostFrequentHelper(TreeNode *&treePtr, int &counter, string &mostFreq);
    void printLeastFrequent(ofstream &file);
    void printLeastFrequentHelper(TreeNode *&treePtr, int &counter, string &leastFreq);
    void printStandartDeviation(ofstream &file);
    void printStandartDeviationHelper(TreeNode *&treePtr, int &totalSum, int data[], int &cnt);
    void generateTree(string inputFileName);
    void removePunctAndLower(string word);
    void createStatistics();

private:
    TreeNode *root;
    int nodeCounter;

friend class TreeNode;
};
#endif // AVLTREE_H_INCLUDED
