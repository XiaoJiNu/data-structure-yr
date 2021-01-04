#ifndef _INSERTSORT_H
#define _INSERTSORT_H


template <typename T>
void insertSort(T arr[], int n){  
    // *** 这里不用返回值，因为数组排序后在外部已经发生变化
    for (int i = 1; i <= n-1; i++){
        // 内层遍历，向前移动元素
        int temp = arr[i];  
        int j;  // 用于记录内层访问的元素位置

        // ##### 版本二
        for (j = i; j-1 >= 0 && temp < arr[j-1]; j--){
            arr[j] = arr[j-1];
        }
        arr[j] = temp;
    }
    return;
}

#endif

