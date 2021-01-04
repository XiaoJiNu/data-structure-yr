#ifndef _SHELLSORT_H
#define _SHELLSORT_H


template <typename T>
void shellSort(T arr[], int n){
    // 确定增量的初始值，增量以3倍的步长缩小
    int h = 1;
    while ( h < n/3){
        h = 3*h +1 ;
    }

    // 开始遍历h，增量以3倍的步长缩小, 将h缩小到1为止
    for (; h >= 1; h = h/3){
        // 每次遍历h时，在数组中遍历下标为[h, h+1, h+2, ... n-1]这些元素，
        // 并对这些元素进行插入排序操作
        for (int i = h; i <= n-1; i++){
            // 每次遍历数组的下标i时，在下标[i, i-h, i-2h, ... i-kh]中，
            // 对下标i对应数组元素进行插入排序操作，其中i-kh >= 0
            T temp = arr[i];  // temp保存当前进行插入排序的元素
            int j = i;        // j用于保存插入排序过程中比较的下标
            for (; j-h >= 0 && temp < arr[j-h]; j = j-h)
                arr[j] = arr[j-h];
            
            // arr[j+h] = temp; 
            arr[j] = temp; 

        }
    }
    return;
}


#endif

