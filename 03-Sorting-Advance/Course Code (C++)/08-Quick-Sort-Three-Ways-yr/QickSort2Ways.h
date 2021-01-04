#ifndef _QUICKSORT2_H
#define _QUICKSORT2_H

#include <stdlib.h>
#include "InsertionSort.h"
using namespace std;

/* 双路快速排序主要用于近乎有序以及大量重复元素的数组排序 */

template <typename T>
int _partition2(T arr[], int L, int R){
    // -----改进点2-----
    // 随机选择一个数，与arr[L]交换位置，作为分割标准
    int randIndex = rand() % (R-L+1) + L;  // 产生[L, R]范围内的随机数下标
    swap(arr[L], arr[randIndex]);
    T temp = arr[L];  

    int i = L+1;  // [L+1, i)范围内存储小于等于temp的元素，初始为空
    int j = R;    // (j, R]存储大于等于temp的元素，初始为空

    // 1. 将 i, j 分别向中间遍历，i 一直遍历到i下标对应元素“大于等于temp终止”，
    //    j 一直遍历到 j 对应元素“小于等于temp终止”。此时[L+1, i)对应元素全部
    //    是小于等于temp，(j, R]对应元素全部大于等于temp。
    // 2. 然后交换arr[i], arr[j]，此时[L+1, i]对应元素全部小于等于temp，
    //    [j, R]范围内元素全部大于等于temp。
    // 3. 继续遍历 i, j，一直到 i > j, 证明此时数组有序，终止partition

    // ----------重点错误1----------
    // 当i==j时，依然需要进行partition操作。比如数组 4,1,2,3,4,5,4,5,5,7
    // 开始时从i=1遍历到i=4, j遍历到j=6,此时arr[i]=4, arr[j]=4
    // 交换arr[i],arr[j]，然后i,j向中间移动一位，i=5==j=5,
    // 此时继续partition操作，arr[i]=5 < temp=4不成立，i没有加1，i=5
    // arr[j]=5 > temp=4成立，j减1，此时j=4，然后i>j成立，终止for循环
    // 此时arr[i]=5, arr[j]=4，此时需要交换arr[j]与arr[L],返回j，此时
    // j就是partition分界点。
    for ( ; i <= j; ){  
        while (i <= R && arr[i] < temp)  i++;  // i向后遍历，arr[i]==temp也会终止
        // while (j >= L && arr[j] > temp)  j--;  // j向前遍历，arr[j]==temp也会终止
        while (j >= L+1 && arr[j] > temp)  j--;  // j向前遍历，arr[j]==temp也会终止

        // if (i >= j) break;                     // ### i 大于等于 j, 终止partition
        if (i > j) break;                     // i 大于 j, 终止partition，等于时不终止操作

        // 交换后，arr[i]==temp也会交换到右边，arr[j]==temp也会
        // 交换到左边，防止等于temp的元素集中在一边
        swap(arr[i], arr[j]);                  
        i++; j--;  // 交换完成，i, j向中间移动一步，继续下一次遍历
        
    }
    // 将[L+1, R]范围内元素分成左右两部分后，[L+1, i]小于等于temp，
    // [i+1, R]大于等于temp。此时交换arr[L],arr[i],则arr[i]==temp，
    // [L, i]部分小于等于temp,[i+1, R]大于等于temp.
    // i就为partition的分界点，返回i
    // swap( arr[L], arr[i]);  // ###
    // return i;               // ###

    // ----------重点错误2----------
    // 这里如果交换L,i，结果将会出错。因为最终的arr[i]对应值可能大于temp，
    // 所以如果arr[L]与arr[i]交换，arr[L]最终可能会大于temp
    // 而最终arr[j]值一定小于等于temp，所以arr[L]与arr[j]交换，
    // 最终arr[L]一定小于等于temp，而交换后的arr[j]==temp，即j为分界点
    swap( arr[L], arr[j]);  // ###
    return j;               // ###

}


template <typename T>
void _qickSort2(T arr[], int L, int R){
    // 递归函数，对arr[L]到arr[R]范围内的元素进行partition操作，partition操作
    // 返回partition后的分界点,同时使arr[L]到arr[p]范围内元素全部小于开始的arr[L]元素，
    // arr[p+1]到arr[R]范围内元素全部大于等于arr[L]
    if (L >= R)
        return;                     // 递归到最底层，此时L=R，终止递归
    
    // -----改进点1-----
    // 如果[L, R]范围内元素个数小于一定数量，直接用插入排序
    // ###
    if ((R - L) < 15){
        insertionSort(arr, L, R);
        return;
    }
    
    int p = _partition2(arr, L, R);  // partition后会返回partition临界点下标
    _qickSort2(arr, L, p-1);
    _qickSort2(arr, p+1, R);

    // return;
}

template <typename T>
void qickSort2(T arr[], int n){
    srand(time(NULL));  // 产生随机数种子

    _qickSort2(arr, 0, n-1);

    return;
}

#endif