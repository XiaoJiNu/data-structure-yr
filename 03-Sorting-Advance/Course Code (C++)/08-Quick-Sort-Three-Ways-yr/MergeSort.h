#ifndef _MERGESORT_H
#define _MERGESORT_H

using namespace std;


template <typename T>
void __merge(T arr[], int L, int mid, int R){
    /* 将arr中[L, mid],[mid+1, R]这两个范围内的有序数组合并成一个有序数组 */
    // 首先生成一个和arr中[L, R]范围内一样元素的数组
    T *aux = new T[R-L+1];
    for (int i = 0; i <= R-L; i++){
        aux[i] = arr[L+i];        
    }
    
    // k从L遍历到R，依次比较aux中mid左右两边的元素，将aux中比较的元素中，小的元素
    // 依赋值给arr[k]，并将这个元素向后移动一位。当k遍历完成，arr中[L, R]范围内元素完成排序
    // ### 这里是对aux中的元素进行比较，所以aux中比较元素的下标应该是i-L, j-L，不是i,j，
    // ### 否则提示segmentation falut
    int i = L, j = mid+1;  // i, j分别初始化为左右两边的第1个下标
    for (int k = L; k <= R; k++){
        if (i > mid){            
            // arr[k] = aux[j];  j++; // 如果mid左边范围内元素排序完成，无需比较，
            arr[k] = aux[j-L];  j++;  // 如果mid左边范围内元素排序完成，无需比较，
        }                             // 直接将右边元素赋值给arr[k]即可，直到k遍历结束
        else if (j > R){
            arr[k] = aux[i-L];  i++;  // 如果mid左边范围内元素排序完成，无需比较，
        }                             // 直接将左边元素赋值给arr[k]即可，直到k遍历结束
        else if (aux[i-L] < aux[j-L]){
            arr[k] = aux[i-L];  i++;  // aux[i]完成排序，将i向后移动一位
        }
        else{
            arr[k] = aux[j-L];  j++;  // aux[j]完成排序，将i向后移动一位
        }
    }

    delete[] aux;                     // new生成的空间需要delete掉
}


template <typename T>
void __mergeSort(T arr[], int L, int R){
    // 先递归[0, mid], [mid+1, R], 再合并
    if (L >= R)
        return;               // 如果L=R，证明此时递归的只有一个元素，终止递归
    int mid = (L + R) / 2;    // mid是数组中间元素下标
    __mergeSort(arr, L, mid);
    __mergeSort(arr, mid+1, R);
    __merge(arr, L, mid, R);  // 递归完成后，对[L, R]范围内元素进行合并
    
}


template <typename T>
void mergeSort(T arr[], int n){
    __mergeSort(arr, 0, n-1);
    return;
}

#endif