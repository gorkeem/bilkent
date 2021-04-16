#ifndef CS202HW1_SORTING_H
#define CS202HW1_SORTING_H


void insertionSort(int *arr, const int size, int &compCount, int &moveCount);
void mergeSort(int *arr, const int size, int &compCount, int &moveCount);
void quickSort(int *arr, const int size, int &compCount, int &moveCount);


// Additional Functions
void partitionn(int *arr, int first, int last, int &pivotIndex,int &compCount,int &moveCount);
void mergee(int *arr, int first, int mid, int last, int &compCount, int &moveCount, int maxArrSize);
void swapp(int &x, int &y);
void calculatorr(int arraySize);
class sorting {

};

#endif //CS202HW1_SORTING_H
