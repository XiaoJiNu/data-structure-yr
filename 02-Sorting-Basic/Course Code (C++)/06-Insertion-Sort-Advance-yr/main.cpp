#include <iostream>

#include "SelectoinSort.h"
#include "InsertSort.h"
#include "SortTestHelper.h"

using namespace SortTestHelper;


int main(){
    // 产生一个随机数组
    int n = 20;  // 数组长度
    int bottom = 0;
    int upper = 3;
    int *arr = SortTestHelper::generateRandomArray(n, bottom, upper);
    
    // 用辅助测试函数来测试排序算法
    SortTestHelper::testSort("selection sort", selectionSort, arr, n);
    SortTestHelper::testSort("insertSort", insertSort, arr, n);

    return 0;
}