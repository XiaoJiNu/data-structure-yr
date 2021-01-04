#include <iostream>
#include <algorithm>
#include "MaxHeap.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "QuickSort2Ways.h"
#include "QuickSort3Ways.h"
#include "SortTestHelper.h"

using namespace std;
                                                                                

// heapSort1, 将所有的元素依次添加到堆中, 在将所有元素从堆中依次取出来, 即完成了排序
// 无论是创建堆的过程, 还是从堆中依次取出元素的过程, 时间复杂度均为O(nlogn)
// 整个堆排序的整体时间复杂度为O(nlogn)
template<typename T>
void heapSort1(T arr[], int n){

    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for( int i = 0 ; i < n ; i ++ )
        maxheap.insert(arr[i]);

    for( int i = n-1 ; i >= 0 ; i-- )
        arr[i] = maxheap.extractMax();

}


// heapSort2, 借助我们的heapify过程创建堆
// 此时, 创建堆的过程时间复杂度为O(n), 将所有元素依次从堆中取出来, 实践复杂度为O(nlogn)
// 堆排序的总体时间复杂度依然是O(nlogn), 但是比上述heapSort1性能更优, 因为创建堆的性能更优
template<typename T>
void heapSort2(T arr[], int n){

    MaxHeap<T> maxheap = MaxHeap<T>(arr,n);
    for( int i = n-1 ; i >= 0 ; i-- )
        arr[i] = maxheap.extractMax();
}


template<typename T>
void __shiftDown(T arr[], int n, int k){

    /*
    n：堆在数组中的元素为0~n
    k: 要进行下移操作的节点序号
    注意：此时堆的节点序号从0开始
    */
    T shiftDownNodeValue = arr[k];  // 记录要进行下移操作的节点的值，便于后面进行赋值操作
    // 没有子节点或者大于等于最大子节点，终止
    while (2*k + 1 <= n){
        int j = 2*k + 1;  // 用j标记k子节点中最大的节点序号
        // 如果右子节点存在且比左子节点大，j存储为右子节点
        if (2*k + 2 <= n && arr[2*k + 1] < arr[2*k + 2]){
           j = 2*k + 2;
        }
        // 如果此时真正要移动的节点值大于或者等于它的子节点中最大的值，终止下移
        // ### if (arr[k] >= arr[j]){
        if (shiftDownNodeValue >= arr[j]){
            break;
        }
        // 如果真正要移动的节点值比它当前k的子节点的最大值要大，交换它们的位置，
        // 但是此时不进行交换操作，而是将要与它交换的节点移动到k节点，但是真正
        // 要下移的节点的值此时不移动
        arr[k] = arr[j];
        k = j;
    }
    
    // 下移终止时，变量k记录此时真正下移的节点的位置，将原始的值赋值给它即可
    arr[k] = shiftDownNodeValue;
}

// heapSort3, 堆原地排序
template<typename T>
void heapSort3(T arr[], int n){
    // Heapify操作
    for (int i = (n-1)/2; i >= 0; i--){
        __shiftDown(arr, n, i);
    }
    // 交换堆顶与堆尾元素，此时堆不再包含堆尾元素，再将堆顶元素进行下移操作
    // 重复上述操作直到存储堆的数组完全有序，即堆只有一个元素终止。此时遍历中的i就代表堆尾的元素序号
    for (int i = n-1; i >= 0; i--){
        swap(arr[i], arr[0]);
        // ### 将堆顶元素进行下移操作，但是此时的堆中只含有数组中0~i-1的元素
        __shiftDown(arr, i-1, 0);
    }
    
    return;
}



// 比较 Merge Sort, 三种 Quick Sort 和本节介绍的两种 Heap Sort 的性能效率
// 注意, 这几种排序算法都是 O(nlogn) 级别的排序算法
int main() {

    int n = 10000000;

    // 测试1 一般性测试
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int* arr1 = SortTestHelper::generateRandomArray(n,0,n);
    int* arr2 = SortTestHelper::copyIntArray(arr1, n);
    int* arr3 = SortTestHelper::copyIntArray(arr1, n);
    int* arr4 = SortTestHelper::copyIntArray(arr1, n);
    int* arr5 = SortTestHelper::copyIntArray(arr1, n);
    int* arr6 = SortTestHelper::copyIntArray(arr1, n);
    int* arr7 = SortTestHelper::copyIntArray(arr1, n);

    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 2 Ways", quickSort2Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr4, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr6, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort3, arr7, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    cout<<endl;


    // 测试2 测试近乎有序的数组
    int swapTimes = 100;
    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr1 = SortTestHelper::generateNearlyOrderedArray(n,swapTimes);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    arr6 = SortTestHelper::copyIntArray(arr1, n);
    arr7 = SortTestHelper::copyIntArray(arr1, n);


    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 2 Ways", quickSort2Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr4, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr6, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort3, arr7, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    cout<<endl;


    // 测试3 测试存在包含大量相同元素的数组
    cout<<"Test for random array, size = "<<n<<", random range [0,10]"<<endl;
    arr1 = SortTestHelper::generateRandomArray(n,0,10);
    arr2 = SortTestHelper::copyIntArray(arr1, n);
    arr3 = SortTestHelper::copyIntArray(arr1, n);
    arr4 = SortTestHelper::copyIntArray(arr1, n);
    arr5 = SortTestHelper::copyIntArray(arr1, n);
    arr6 = SortTestHelper::copyIntArray(arr1, n);
    arr7 = SortTestHelper::copyIntArray(arr1, n);


    SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
    // 这种情况下, 普通的QuickSort退化为O(n^2)的算法, 不做测试
    //SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
    SortTestHelper::testSort("Quick Sort 2 Ways", quickSort2Ways, arr3, n);
    SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr4, n);
    SortTestHelper::testSort("Heap Sort 1", heapSort1, arr5, n);
    SortTestHelper::testSort("Heap Sort 2", heapSort2, arr6, n);
    SortTestHelper::testSort("Heap Sort 3", heapSort3, arr7, n);


    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    return 0;
}