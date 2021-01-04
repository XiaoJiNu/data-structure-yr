#include <iostream>

#include "SelectoinSort.h"
#include "InsertSort.h"
#include "BubbleSort.h"
#include "ShellSort.h"
#include "SortTestHelper.h"

using namespace SortTestHelper;


int main(){
    // 产生一个随机数组
    int n = 100000;  // 数组长度
    int bottom = 0;
    int upper = n;
    int *arr1 = SortTestHelper::generateRandomArray(n, bottom, upper);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr4 = SortTestHelper::copyIntArray(arr1, n);
    // SortTestHelper::showArray(arr1, n); cout << endl;
    // SortTestHelper::showArray(arr2, n); cout << endl;
    // SortTestHelper::showArray(arr3, n); cout << endl;
    // SortTestHelper::showArray(arr4, n); cout << endl;

    // 用辅助测试函数来测试排序算法
    // SortTestHelper::testSort("selection sort", selectionSort, arr1, n);
    // SortTestHelper::testSort("insertSort", insertSort, arr2, n);
    // SortTestHelper::testSort("bubble sort", bubbleSort, arr3, n);
    SortTestHelper::testSort("shell sort", shellSort, arr4, n);


    // 测试近乎有序的数组
    int swapTime = 100;
    int *nearlyOrderedArr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTime);
    int *nearlyOrderedArr2 = SortTestHelper::copyIntArray(nearlyOrderedArr1, n);
    int *nearlyOrderedArr3 = SortTestHelper::copyIntArray(nearlyOrderedArr1, n);
    int *nearlyOrderedArr4 = SortTestHelper::copyIntArray(nearlyOrderedArr1, n);
    // SortTestHelper::testSort("selection sort", selectionSort, nearlyOrderedArr1, n);
    // SortTestHelper::testSort("insertSort", insertSort, nearlyOrderedArr2, n);
    // SortTestHelper::testSort("bubble sort", bubbleSort, nearlyOrderedArr3, n);
    SortTestHelper::testSort("shell sort", shellSort, nearlyOrderedArr4, n);


    return 0;
}

