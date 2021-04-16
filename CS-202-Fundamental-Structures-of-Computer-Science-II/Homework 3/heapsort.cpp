#include "heap.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;


int main(int argc, char** argv){

    int numberOfElements = 0;

    ifstream inputFile;
    inputFile.open(argv[1]);

    // Get total number of elements in input file
    string number;
    while (inputFile >> number) {
        numberOfElements++;
    }

    //Creates a heap of given input file's number size
    Heap h(numberOfElements);

    // Go back to file's top position
    inputFile.clear();
    inputFile.seekg(0);

    //Inserts each numbers in the file to the heap
    while (inputFile >> number) {
        h.insert(atoi(number.c_str()));
    }

    inputFile.close();

    // DO HEAPSORT
    for(int index = (h.size /2)-1; index >= 0; index--){
        h.heapRebuild(index, h.size);
    }

    for(int last = h.size - 1; last >0; last--){
        swap(h.items[0], h.items[last]);
        h.heapRebuild(0, last);
    }

    // create the output file and fill it
    ofstream outputFile;
    outputFile.open(argv[2]);

    for(int i = 0; i < h.size; i++){
        // cout << h.items[i] << endl;
        outputFile << h.items[i] << "\n";
    }

    // Prints number of elements and number of comparisons
    cout << "n = " << numberOfElements << ", Number of comparisons = " << h.getCompCount() << endl;
    outputFile.close();
    

    return 0;
}



