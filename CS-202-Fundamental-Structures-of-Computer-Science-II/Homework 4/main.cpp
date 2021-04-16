#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "AVLTreeNode.h"
#include "AVLTree.h"

using namespace std;

int main(int argc, char **argv){
    AVLTree A;

    string fileName = argv[1];
    A.generateTree(fileName);
    return 0;
}