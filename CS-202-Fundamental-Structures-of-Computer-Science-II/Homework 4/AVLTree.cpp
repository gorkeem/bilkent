#include <iostream>
// #include <stdio.h>
#include <math.h>
#include "AVLTree.h"
#include "AVLTreeNode.h"
#include <fstream> // for read/write file
#include <string> // for removing punctuations in words
#include <climits> // for max integer
#include <algorithm> // for the string replace function
#include <vector>

using namespace std;

AVLTree::AVLTree(){
    root = NULL;
    nodeCounter = 0;
}
AVLTree::AVLTree(const AVLTree &tree){
    nodeCounter = 0;
}


AVLTree::~AVLTree(){}

void AVLTree::addWord(string key){
    insertItem(root, key);
}
void AVLTree::insertItem(TreeNode *&treePtr, const string &newItem){
    // Position of insertion found; insert after leaf
    if(treePtr == NULL){
        treePtr = new TreeNode(newItem, NULL, NULL);
        nodeCounter = nodeCounter + 1;
    }
    else{
        if(newItem == treePtr->item){
            treePtr->count++;
        }
        else if(newItem < treePtr->item){
            insertItem(treePtr->left, newItem);
            if (getBalance(treePtr) > 1) { //check for any imbalance
                if (newItem < treePtr->left->item) { //perform rotations if necessary
                    singleRightRotation(treePtr);
                } else {
                    doubleLeftRightRotation(treePtr);
                }
            }
        }
        else{
            insertItem(treePtr->right, newItem);
            if (getBalance(treePtr) < -1) {
                if (newItem >= treePtr->right->item) {
                    singleLeftRotation(treePtr);
                } else {
                    doubleRightLeftRotation(treePtr);
                } 
            }
        }
    }
    treePtr->height = 1 + max(getHeight(treePtr->left), getHeight(treePtr->right));
}

int AVLTree::getHeight(TreeNode *&treePtr){
    if(treePtr == NULL){
        return 0;
    }
    return treePtr->height;
}

void AVLTree::singleLeftRotation(TreeNode *&treePtr){
    TreeNode* temp = treePtr;
    treePtr = treePtr->right;
    temp->right = treePtr->left;
    treePtr->left = temp;
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right)); //height updates after rotation
    treePtr->height = 1 + max(getHeight(treePtr->left), getHeight(treePtr->right));
}
void AVLTree::singleRightRotation(TreeNode *&treePtr){
    TreeNode* temp = treePtr;
    treePtr = treePtr->left;
    temp->left = treePtr->right;
    treePtr->right = temp;
    temp->height = 1 + max(getHeight(temp->left), getHeight(temp->right)); //height updates after rotation
    treePtr->height = 1 + max(getHeight(treePtr->left), getHeight(treePtr->right));
}
void AVLTree::doubleLeftRightRotation(TreeNode *&treePtr){
    singleLeftRotation(treePtr->left);
    singleRightRotation(treePtr);
}
void AVLTree::doubleRightLeftRotation(TreeNode *&treePtr){
    singleRightRotation(treePtr->right);
    singleLeftRotation(treePtr);
}
int AVLTree::getBalance(TreeNode *&treePtr){
     return getHeight(treePtr->left) - getHeight(treePtr->right);
}

// Homework Functions
// Function that prints the tree height
void AVLTree::printHeight(ofstream &file){

    file.open("statistics.txt", ios_base::app);
    file << "Tree Height: " << getHeight(root) << "\n";
    file.close();
}
// Function that prints the total word count and its helper function
void AVLTree::printTotalWordCount(ofstream &file){
    int totalCount = 0;
    printTotalWordCountHelper(root, totalCount);

    file.open("statistics.txt", ios_base::app);
    file << "Total Word Count: " << totalCount << "\n";
    file.close();

}
void AVLTree::printTotalWordCountHelper(TreeNode *&treePtr, int &totalCount){

    if(treePtr == NULL)
        return;
    else{
        printTotalWordCountHelper(treePtr->left, totalCount);
        totalCount += treePtr->count;
        printTotalWordCountHelper(treePtr->right, totalCount);
    }
    
}
// recursively prints each unique word in the tree in alphabetical order along with their frequencies in the text file.
void AVLTree::printWordFrequencies(){
    // cout << "Printing words and frequencies in alphabetic order: " << endl;
    ofstream wordFreqs;
    printWordFrequenciesHelper(root, wordFreqs);
}
void AVLTree::printWordFrequenciesHelper(TreeNode *&treePtr, ofstream &file){

    if(treePtr == NULL)
        return;
    else{
        printWordFrequenciesHelper(treePtr->left, file);

        file.open("wordFreqs.txt", ios_base::app);
        // cout << treePtr->item << " " << treePtr->count << endl;
        file << treePtr->item << " " << treePtr->count << "\n";
        file.close();


        printWordFrequenciesHelper(treePtr->right, file);
    }
}
// function that prints the most frequent word
void AVLTree::printMostFrequent(ofstream &file){
    int counter = 0;
    string mostFreq = "";

    printMostFrequentHelper(root, counter, mostFreq);

    file.open("statistics.txt", ios_base::app);
    file << "Most Frequent: " << mostFreq << " " << counter << "\n";
    file.close();
}
void AVLTree::printMostFrequentHelper(TreeNode *&treePtr, int &counter, string &mostFreq){
    if(treePtr == NULL)
        return;
    else{
        printMostFrequentHelper(treePtr->left, counter, mostFreq);
        if(treePtr->count > counter){
            counter = treePtr->count;
            mostFreq = treePtr->item;
        }
        printMostFrequentHelper(treePtr->right, counter, mostFreq);
    } 
}
// function that prints the least frequent word
void AVLTree::printLeastFrequent(ofstream &file){
    int counter = INT_MAX;
    string leastFreq = "";

    printLeastFrequentHelper(root, counter, leastFreq);
    file.open("statistics.txt", ios_base::app);
    file << "Least Frequent: " << leastFreq << " " << counter << "\n";
    file.close();
}
void AVLTree::printLeastFrequentHelper(TreeNode *&treePtr, int &counter, string &leastFreq){
    if(treePtr == NULL)
        return;
    else{
        printLeastFrequentHelper(treePtr->left, counter, leastFreq);
        if(treePtr->count < counter){
            counter = treePtr->count;
            leastFreq = treePtr->item;
        }
        printLeastFrequentHelper(treePtr->right, counter, leastFreq);
    } 
}
// function that prints the standart deviation
void AVLTree::printStandartDeviation(ofstream &file){
    float sum = 0.0;
    float mean = 0.0;
    float standardDeviation = 0.0;

    int totalSum = 0;
    int totalNodes = nodeCounter;

    int *freq = new int[totalNodes];
    int cnt = 0;

    printStandartDeviationHelper(root, totalSum, freq, cnt);

    mean = totalSum / totalNodes;

    for(int i = 0; i < totalNodes; i++)
        standardDeviation += pow(freq[i] - mean, 2);

    delete freq;
    file.open("statistics.txt", ios_base::app);
    file << "Standart Deviation: " << sqrt(standardDeviation / totalNodes) << "\n";
    file.close();
}
void AVLTree::printStandartDeviationHelper(TreeNode *&treePtr, int &totalSum, int data[], int &cnt){
    if(treePtr == NULL)
        return;
    else{
        printStandartDeviationHelper(treePtr->left, totalSum, data, cnt);
        totalSum = totalSum + treePtr->count;
        data[cnt] = treePtr->count;
        cnt += 1;
        printStandartDeviationHelper(treePtr->right, totalSum, data, cnt);
    } 

}
// Function that generates the tree by reading input text file
void AVLTree::generateTree(string inputFileName){
    ifstream file;
    file.open(inputFileName.c_str());

    string word;
    while (file >> word)
    {
        removePunctAndLower(word); 
    }
    printWordFrequencies();
    createStatistics();
}
void AVLTree::removePunctAndLower(string word){
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    replace(word.begin(), word.end(), '\'', ' ');

    for (int i = 0, len = word.size(); i < len; i++) 
    { 
        // check whether parsing character is punctuation or not 
        if (ispunct(word[i]) || isdigit((char)word[i])) 
        { 
            word.erase(i--, 1); 
            len = word.size(); 
        } 
    }

    string temp = "";
    vector<string> v;
	for(int i=0;i<word.length();++i){
		
		if(word[i]==' '){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(word[i]);
		}
		
	}
	v.push_back(temp);
    for(int i=0;i<v.size();++i){
        addWord(v[i]);
    }
		
}
void AVLTree::createStatistics(){
    ofstream file;

    printTotalWordCount(file);
    printHeight(file);
    printMostFrequent(file);
    printLeastFrequent(file);
    printStandartDeviation(file);

}