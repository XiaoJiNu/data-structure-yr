#include <iostream>
#include "SortTestHelper.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "MergeSortOptimal.h"
#include "QickSort.h"

using namespace std;


int main() {

    int n = 10000000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);

    // SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    SortTestHelper::testSort("Merge Sort",   mergeSort,  arr2, n);
    SortTestHelper::testSort("Merge Sort 2", mergeSort2, arr3, n);
    SortTestHelper::testSort("Qick Sort",    qickSort,   arr4, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    // ### 对于近乎有序的数组，快速排序的时间复杂度退化成O(n^2)
    // int swapTimes = 10;
    // assert( swapTimes >= 0 );

    // cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    // arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    // arr2 = SortTestHelper::copyIntArray(arr1, n);
    // arr3 = SortTestHelper::copyIntArray(arr1, n);
    // arr4 = SortTestHelper::copyIntArray(arr1, n);

    // SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    // SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);
    // SortTestHelper::testSort("Merge Sort 2",   mergeSort2,    arr3, n);
    // SortTestHelper::testSort("Qick Sort",      qickSort,      arr4, n);

    // delete[] arr1;
    // delete[] arr2;
    // delete[] arr3;
    // delete[] arr4;

    return 0;
}