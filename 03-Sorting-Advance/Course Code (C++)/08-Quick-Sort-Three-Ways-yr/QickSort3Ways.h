#ifndef _QUICKSORT3WAYS_H
#define _QUICKSORT3WAYS_H

#include <stdlib.h>
#include "InsertionSort.h"
using namespace std;

/* 三路快速排序主要用于近乎有序以及大量重复元素的数组排序，对双路快速排序进一步优化 */


template <typename T>
void _qickSort3(T arr[], int L, int R){
 
    if (L >= R)
        return;                     // 递归到最底层，此时L=R，终止递归
    
    // -----改进点1-----
    // 如果[L, R]范围内元素个数小于一定数量，直接用插入排序
    if ((R - L) < 15){
        insertionSort(arr, L, R);
        return;
    }
    
    // ----------partition开始----------
    // 三路快速排序的partition用一个函数处理，返回值不好处理，所以不用函数
    // 随机选择一个数作为分割点
    swap(arr[L], arr[rand()%(R-L+1)+L]);
    T temp = arr[L];

    // 每次partition后让[L, lt]小于temp, [lt+1, gt] []
    int lt = L, gt = R + 1, i = L+1;
    while ( i < gt){
        if (arr[i] < temp){  
            swap(arr[i], arr[lt+1]);
            i++; lt++;
        }
        else if(arr[i] > temp){
            swap(arr[i], arr[gt-1]);
            gt--;
        }
        else
            i++;
    }
    // i遍历结束时，交换arr[L]和arr[lt]，然后lt减1，最终partition完成
    swap(arr[L], arr[lt]);
    lt--;
    // ----------partition结束----------

    // partition结束，继续递归[L, lt], [gt, R],直到完成排序
    _qickSort3(arr, L, lt);
    _qickSort3(arr, gt, R);
}


template <typename T>
void qickSort3(T arr[], int n){
    srand(time(NULL));  // 产生随机数种子

    _qickSort3(arr, 0, n-1);

    return;
}

#endif