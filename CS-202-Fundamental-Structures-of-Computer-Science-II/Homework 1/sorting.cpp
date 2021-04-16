#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;



void insertionSort(int *arr, int first, int last, int &compCount, int &moveCount){

    for(int unsorted = 1; unsorted < last + 1; unsorted++){
        int nextItem = arr[unsorted];
        compCount++;
        int loc = unsorted;

        for(; (loc > 0) && (arr[loc - 1] > nextItem); loc--){
            arr[loc] = arr[loc - 1];
            moveCount++;
            compCount++;

        }
        arr[loc] = nextItem;
        compCount++;
    }
}
void insertionSort(int *arr, const int size, int &compCount, int &moveCount){

    insertionSort( arr, 0, size-1, compCount, moveCount);

}

void mergeSort(int *arr, int first, int last, int &compCount, int &moveCount){

    if(first < last){


        int mid = (first + last) / 2; //index of the midpoint

        mergeSort(arr, first, mid, compCount, moveCount);
        mergeSort(arr, mid + 1, last, compCount, moveCount);

        //now combine the halves
        mergee(arr, first, mid, last, compCount, moveCount, last + 1);
    }

}

void mergee(int *theArray, int first, int mid, int last, int &compCount, int &moveCount, int maxArrSize){
    int tempArray[maxArrSize]; //temporary array

    //initialize the local indices to indicate the subarrays
    int first1 = first;     //beginning of the first sub array
    int last1 = mid;        //end of the first subarray
    int first2 = mid + 1;   //Beginning of the second subarray
    int last2 = last;       //End of the second subarray
    int index = first1;     // Next available location in tempArray


    for ( ;(first1 <= last1) && (first2 <= last2); ++index) {
        if(theArray[first1] < theArray[first2]) {
            tempArray[index] = theArray[first1];
            first1++;
        }

        else{
            tempArray[index] = theArray[first2];
            first2++;
        }
        moveCount++;
        compCount++;
    }
    // finish off the first subarray, if necessary
    for(; first1 <= last1; ++first1, ++index){
        tempArray[index] = theArray[first1];
        moveCount++;
    }

    // finish off the second subarray, if necessary
    for (; first2 <= last2; ++first2, ++index){
        tempArray[index] = theArray[first2];
        moveCount++;
    }

    // copy the result back into the original array
    for (index = first; index <= last; ++index){
        theArray[index] = tempArray[index];
        moveCount++;
    }


} // end mergesort
void mergeSort(int *arr, const int size, int &compCount, int &moveCount){

    mergeSort( arr, 0, size-1, compCount, moveCount);

}

void swapp(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}


void quickSort(int *arr, int first, int last, int &compCount, int &moveCount){
    int pivotIndex = arr[first];
    moveCount++;

    if(first < last){
        partitionn(arr, first, last, pivotIndex, compCount, moveCount);
        quickSort(arr, first, pivotIndex - 1, compCount, moveCount);
        quickSort(arr, pivotIndex + 1, last, compCount, moveCount);
    }
}
void partitionn(int *arr, int first, int last, int &pivotIndex,int &compCount,int &moveCount){
    // Precondition: theArray[first..last] is an array; first <= last.
    // Postcondition: Partitions theArray[first..last] such that:
    //   S1 = theArray[first..pivotIndex-1] < pivot
    //   theArray[pivotIndex] == pivot
    //   S2 = theArray[pivotIndex+1..last] >= pivot

    swapp(arr[first], arr[last]);
    moveCount = moveCount + 3;

    int pivot = arr[first];
    moveCount++;

// initially, everything but pivot is in unknown
    int lastS1 = first;           // index of last item in S1
    int firstUnknown = first + 1; // index of first item in unknown

    // move one item at a time until unknown region is empty
    for (  ; firstUnknown <= last; ++firstUnknown) {
        // Invariant: theArray[first+1..lastS1] < pivot
        //            theArray[lastS1+1..firstUnknown-1] >= pivot

        // move item from unknown to proper region
        if (arr[firstUnknown] < pivot) {  	// belongs to S1        // INC
            compCount++;

            ++lastS1;

            //swapping part
            swapp(arr[firstUnknown], arr[lastS1]);
            moveCount = moveCount + 3;
        }	// else belongs to S2
    }
    // place pivot in proper position and mark its location
    //swap(theArray[first], theArray[lastS1]);
    //swapping part 2
    swapp(arr[first], arr[lastS1]);

    moveCount = moveCount + 3;
    pivotIndex = lastS1;
}
void quickSort(int *arr, const int size, int &compCount, int &moveCount){

    quickSort( arr, 0, size-1, compCount, moveCount);

}
void calculatorr(int arrSize){
    cout << "For " << arrSize << " size" << endl;

    int *arr1 = new int[arrSize];
    int *arr2 = new int[arrSize];
    int *arr3 = new int[arrSize];


    int compCountInsertion1 = 0;
    int compCountInsertion2 = 0;
    int compCountInsertion3 = 0;

    int compCountMerge1 = 0;
    int compCountMerge2 = 0;
    int compCountMerge3 = 0;

    int compCountQuick1 = 0;
    int compCountQuick2 = 0;
    int compCountQuick3 = 0;


    int moveCountInsertion1 = 0;
    int moveCountInsertion2 = 0;
    int moveCountInsertion3 = 0;

    int moveCountMerge1 = 0;
    int moveCountMerge2 = 0;
    int moveCountMerge3 = 0;

    int moveCountQuick1 = 0;
    int moveCountQuick2 = 0;
    int moveCountQuick3 = 0;


    //RANDOM
    //filling with random numbers
    for(int i = 0; i < arrSize; i++){
        arr1[i] = rand();
        arr2[i] = rand();
        arr3[i] = rand();
    }
    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Random integers " << "\t" << "Elapsed Time " << "\t" << "compCount " << "\t" << "moveCount" << endl;

    clock_t startTime = clock();
    double duration;
    insertionSort(arr1, 0, arrSize - 1, compCountInsertion1, moveCountInsertion1);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Insertion sort " << "\t\t" << duration << "\t\t" << compCountInsertion1 << "\t\t" << moveCountInsertion1 << endl;

    startTime = clock();
    mergeSort(arr2, 0, arrSize - 1, compCountMerge1, moveCountMerge1);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Merge sort " << "\t\t" << duration << "\t\t" << compCountMerge1 << "\t\t" << moveCountMerge1 << endl;

    startTime = clock();
    quickSort(arr3, 0, arrSize - 1, compCountQuick1, moveCountQuick1);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Quick sort " << "\t\t" << duration << "\t\t" << compCountQuick1 << "\t\t" << moveCountQuick1 << endl;


    //ascending order
    for(int i = 0; i < arrSize; i++){
        arr1[i] = i;
        arr2[i] = i;
        arr3[i] = i;
    }

    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Ascending integers " << "\t" << "Elapsed Time " << "\t" << "compCount " << "\t" << "moveCount" << endl;


    startTime = clock();
    insertionSort(arr1, 0, arrSize - 1, compCountInsertion2, moveCountInsertion2);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Insertion sort " << "\t\t" << duration << "\t\t" << compCountInsertion2 << "\t\t" << moveCountInsertion2 << endl;

    startTime = clock();
    mergeSort(arr2, 0, arrSize - 1, compCountMerge2, moveCountMerge2);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Merge sort " << "\t\t" << duration << "\t\t" << compCountMerge2 << "\t\t" << moveCountMerge2 << endl;

    startTime = clock();
    quickSort(arr3, 0, arrSize - 1, compCountQuick2, moveCountQuick2);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Quick sort " << "\t\t" << duration << "\t\t" << compCountQuick2 << "\t\t" << moveCountQuick2 << endl;


    //descending order

    int reverseFill = arrSize;
    for(int i = 0; i < arrSize; i++){
        arr1[i] = reverseFill;
        arr2[i] = reverseFill;
        arr3[i] = reverseFill;
        reverseFill--;
    }

    cout << "------------------------------------------------------------------------------------------" << endl;
    cout << "Descending integers " << "\t" << "Elapsed Time " << "\t" << "compCount " << "\t" << "moveCount" << endl;

    startTime = clock();
    insertionSort(arr1, 0, arrSize - 1, compCountInsertion3, moveCountInsertion3);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Insertion sort " << "\t\t" << duration << "\t\t" << compCountInsertion3 << "\t\t" << moveCountInsertion3 << endl;

    startTime = clock();
    mergeSort(arr2, 0, arrSize - 1, compCountMerge3, moveCountMerge3);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Merge sort " << "\t\t" << duration << "\t\t" << compCountMerge3 << "\t\t" << moveCountMerge3 << endl;

    startTime = clock();
    quickSort(arr3, 0, arrSize - 1, compCountQuick3, moveCountQuick3);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Quick sort " << "\t\t" << duration << "\t\t" << compCountQuick3 << "\t\t" << moveCountQuick3 << endl;

    cout << endl << endl;

    delete [] arr1;
    delete [] arr2;
    delete [] arr3;
}
