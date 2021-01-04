#include <iostream>
#include "SortTestHelper.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "MergeSortOptimal.h"
#include "QickSort.h"
#include "QickSort2Ways.h"
#include "QickSort3Ways.h"



using namespace std;


int main() {

    int n = 1000000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n, 0, n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);
    int* arr5 = SortTestHelper::copyIntArray(arr1, n);

    // SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    // SortTestHelper::testSort("Merge Sort",   mergeSort,  arr2, n);
    SortTestHelper::testSort("Merge Sort 2", mergeSort2, arr3, n);
    SortTestHelper::testSort("Qick Sort 2",    qickSort2,   arr4, n);
    SortTestHelper::testSort("Qick Sort 3",    qickSort3,   arr5, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    // ### 对于近乎有序的数组，快速排序的时间复杂度退化成O(n^2)
    int swapTimes = 1000;
    assert( swapTimes >= 0 );

    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);

    // SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    // SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);
    SortTestHelper::testSort("Merge Sort 2",   mergeSort2,     arr3, n);
    SortTestHelper::testSort("Qick Sort 2",    qickSort2,      arr4, n);
    SortTestHelper::testSort("Qick Sort 3",    qickSort3,      arr5, n);

    
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;

    // 测试3 测试大量重复元素的数组
    cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
    arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    int* arr6 = SortTestHelper::copyIntArray(arr1, n);


    // SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    // SortTestHelper::testSort("Merge Sort",     mergeSort,     arr2, n);
    SortTestHelper::testSort("Merge Sort 2",   mergeSort2,    arr3, n);
    // SortTestHelper::testSort("Qick Sort",      qickSort,      arr4, n);
    SortTestHelper::testSort("Qick Sort2",     qickSort2,     arr5, n);
    SortTestHelper::testSort("Qick Sort 3",    qickSort3,     arr6, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;

    return 0;
}