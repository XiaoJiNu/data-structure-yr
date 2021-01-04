#include <iostream>

#include "SortTestHelper.h"

using namespace SortTestHelper;

/* 传入数组和数组长度，输出从小到大排序好的元素。
    先遍历外层元素，每次遍历外层元素时，开始时令minIndex值为当前遍历元素的下标，
    内层再遍历外层当前遍历元素之后的元素，从中选择最小的值的下标赋值给minIndex，
    最后minIndex就是此次外层遍历中选择出来的最小元素，交换外层当前访问元素和minIndex对应元素 */
template <typename T>
void selectionSort(T arr[], int n){  
    // *** 这里不用返回值，因为数组排序后在外部已经发生变化
    for (int i = 0; i < n; i++){
        int minIndex = i;  
        // for (int j = i+1; i < n; j++){  // 应该是j < n
        for (int j = i+1; j < n; j++){     // 这里不用担心数组越界，因为j < n时会终止遍历
            // if (arr[j] < arr[i])        // 应该是每个j对应元素与当前最小的值比较
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        swap(arr[i], arr[minIndex]);  // 每次内层循环完成后，交换找到的最小值与外层遍历的当前值
    }
}

int main(){
    // 产生一个随机数组
    int n = 10;  // 数组长度
    int bottom = 0;
    int upper = 100;
    int *arr = SortTestHelper::generateRandomArray(n, bottom, upper);
    
    // 用辅助测试函数来测试排序算法
    SortTestHelper::testSort("selection sort", selectionSort, arr, n);

    return 0;
}