#include <stdlib.h>
#include <string.h>
#pragma once

void merge(int *array1, int *array2, size_t size1, size_t size2) { // shuffles array2 into array1. array1 should have everything
    int *internalArray = (int *)malloc((size1 + size2) * sizeof(int));
    size_t array1Index = 0; 
    size_t array2Index = 0;
    size_t totalSize = size1 + size2;
    while ((array1Index < size1) && (array2Index < size2)) {
        if (array1[array1Index] < array2[array2Index]) {
            internalArray[array1Index + array2Index] = array1[array1Index];
            array1Index++;
        } else {
            internalArray[array1Index + array2Index] = array2[array2Index];
            array2Index++;
        }
    }
    while (array1Index < (size1)) {
        internalArray[array1Index + array2Index] = array1[array1Index];
        array1Index++;
    }
    while (array2Index < (size2)) {
        internalArray[array1Index + array2Index] = array2[array2Index];
        array2Index++;
    }
    memcpy(array1, internalArray, totalSize * sizeof(int));
    free(internalArray);
    return;
}

static inline size_t partition(size_t size) { // returns index to second array
    return size / 2UL;
}

void mergeSort(int *array1, size_t sizeTotal) {
    size_t partition2Index = partition(sizeTotal); // also size of first partition
    int *array2 = array1 + partition2Index;
    size_t size1 = partition2Index;
    size_t size2 = sizeTotal - partition2Index;
    if (sizeTotal <=1) return;
    mergeSort(array1, size1);
    mergeSort(array2, size2);
    merge(array1, array2, size1, size2);
    return;
}