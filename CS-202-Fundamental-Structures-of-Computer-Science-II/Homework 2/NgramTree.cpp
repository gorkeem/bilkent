#include <iostream>
#include <stdio.h>
#include <math.h>
#include "NgramTree.h"
#include "PbBSTNode.h"
#include <fstream>
using namespace std;



NgramTree::NgramTree(){
    root = NULL;
    nodeCounter = 0;
}
NgramTree::NgramTree(const NgramTree &tree){
    nodeCounter = 0;
}


NgramTree::~NgramTree(){}

// search tree retrieve and retrieve functions

void NgramTree::insertKey(string key){
    insertItem(root, key);
}
void NgramTree::insertItem(TreeNode *&treePtr, const string &newItem){

		// TODO
	if ( treePtr == NULL ){
		treePtr = new TreeNode( newItem, NULL, NULL, 1);
		nodeCounter++;
	}
	
	else if (newItem.compare(treePtr->item) > 0)
		insertItem( treePtr->rightChildPtr, newItem);
	else if ( newItem.compare(treePtr->item) < 0 )
		insertItem( treePtr->leftChildPtr, newItem);
	else{
		if(newItem.compare(treePtr->item) == 0){
			treePtr->count++;
			nodeCounter++;
		}
			
	}
}

int NgramTree::getHeight(){
    if(root == NULL){
        return 0;
    }
    return doHeight(root);

}
int NgramTree::doHeight(TreeNode *&treePtr){
    if (treePtr == NULL)
   {
      return 0;
   }
   int heightOfLeft = doHeight(treePtr->leftChildPtr);
   int heightOfRight = doHeight(treePtr->rightChildPtr);
       if (heightOfLeft > heightOfRight){
            return(heightOfLeft + 1);
       }
       else{
            return(heightOfRight + 1);
       }
}


int NgramTree::getNodeCount(){
    return nodeCounter;
}
int NgramTree::findNodesRequired(){
    return (pow(2, getHeight()) - 1) - nodeCounter;
}
void NgramTree::addNgram(string ngram){
	insertKey(ngram);
}

int NgramTree::getTotalNgramCount(){
	int cnt = 0;
	getTotalNgramCountHelper(root, cnt);
	return cnt;
}
void NgramTree::getTotalNgramCountHelper(TreeNode *&treePtr, int &cnt){
	if(treePtr != NULL){
		//if not null, count increment
		cnt++;
		getTotalNgramCountHelper(treePtr->leftChildPtr, cnt);
		getTotalNgramCountHelper(treePtr->rightChildPtr, cnt);
	}
}

bool NgramTree::isComplete(){
	int index = 0;
	int nodeCount = getNodeCount();

	return isCompleteHelper(root, index, nodeCount);
	
}
bool NgramTree::isCompleteHelper(TreeNode *&root, int index, int nodeCount){
	// An empty tree is complete 
    if (root == NULL) 
        return true; 
  
    // If index assigned to current node is more than 
    // number of nodes in tree, then tree is not complete 
    if (index >= nodeCount) 
        return false; 
  
    // Recursively check left and right subtrees. 
    return (isCompleteHelper(root->leftChildPtr, 2*index + 1, nodeCount) && 
            isCompleteHelper(root->rightChildPtr, 2*index + 2, nodeCount)); 
}
bool NgramTree::isFull(){
	int ngram= getTotalNgramCount();
	int height = getHeight();
	

	if (pow(2, height) - 1 == ngram)
		return true;
	else
		return false;
}
void NgramTree::generateTree(string filename, int n){

	// print the sentences in input.txt
	ifstream file(filename.c_str());
  	string str;
	while (getline(file, str)) {
		cout << str << "\n";
	}

	ifstream ff;
	ff.open(filename.c_str());
	string word;

	while (ff >> word){
		if (word.length() >= n)
			generateTreeHelper(word, n);
	}
        
}
void NgramTree::generateTreeHelper(string token, int n){
	if(n <= token.length()){
		for(int i = 0; i <= token.length() - n; ++i){
			addNgram(token.substr(i, n));
		}
	}
}
// (From lecture note 3)
ostream& NgramTree::print( ostream& out ) const {
    
  return printHelper( out, root );
}

// private helper function  --- inorder traversal (prints in sorted order)
ostream& NgramTree::printHelper( ostream& out, TreeNode* root ) const {
    
  if ( root != NULL ) {
    printHelper( out, root->leftChildPtr );
    out << "\"" << root->item << "\"" << " appears " << root->count << " time(s) " <<   endl;
    printHelper( out, root->rightChildPtr );
  }
  return out;
}

ostream& operator<<( ostream& out, NgramTree &tree ) {
    
  return tree.print( out );

}
