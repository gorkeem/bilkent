#include "heap.h"
#include <iostream>
// #include <stdlib.h>
using namespace std;

// Default constructor 
Heap::Heap() : size(0) {
	items = new int[100]; //100 is default
	compCount = 0;
	maxNumOfElements = 100;
}
Heap::Heap(int elementSize){
	items = new int[elementSize];
	size = 0;
	compCount = 0;
	maxNumOfElements = elementSize;
}
Heap::~Heap(){
	delete items;
}


bool Heap::heapIsEmpty() const {
	return (size == 0);
}
void Heap::heapInsert(const int& newItem){

	if (size >= maxNumOfElements)
		cout << "Heap is full" << endl;

	// Place the new item at the end of the heap
	items[size] = newItem;

	// Trickle new item up to its proper position
	int place = size;
	int parent = (place - 1)/2;
	while ( (place > 0) && (items[place] > items[parent]) ) {
		int temp = items[parent];
		items[parent] = items[place];
		items[place] = temp;

		place = parent;
		parent = (place - 1)/2;

		compCount++;
	}
 	++size;
}
void Heap::heapDelete(int& rootItem){
	if (heapIsEmpty())
		cout << "Heap is already EMPTY" << endl;
	else {
		rootItem = items[0];
		items[0] = items[--size];
		heapRebuild(0, size);
	}
}
void Heap::heapRebuild(int root, int size) {   
	int child = 2 * root + 1; 	// index of root's left child, if any
	if ( child < size ) {		
		// root is not a leaf so that it has a left child
		int rightChild = child + 1; 	// index of a right child, if any
		// If root has right child, find larger child
		if ( (rightChild < size) && (items[rightChild] >items[child])){
			child = rightChild; 	// index of larger child
			compCount++;
		}
			

		// If root’s item is smaller than larger child, swap values
		if (items[root] < items[child]) {
			compCount++;

			int temp = items[root];
			items[root] = items[child];
			items[child] = temp;

			// transform the new subtree into a heap
			heapRebuild(child, size);
		}
    }
}

void Heap::insert(const int a){
    if (size >= maxNumOfElements)
		cout << "Heap is full" << endl;

	// Place the new item at the end of the heap
	items[size] = a;

	// Trickle new item up to its proper position
	int place = size;
	int parent = (place - 1)/2;
	while ( (place > 0) && (items[place] > items[parent]) ) {

		compCount++;
		int temp = items[parent];
		items[parent] = items[place];
		items[place] = temp;

		place = parent;
		parent = (place - 1)/2;
	}
 	++size;
}
int Heap::maximum(){
    return items[0];
}
int Heap::popMaximum(){
    heapDelete(items[0]);
    return 0;
}

int Heap::getCompCount(){
	return compCount;
}