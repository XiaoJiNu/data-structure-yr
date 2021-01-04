#ifndef _INSERTSORT_H
#define _INSERTSORT_H


/*  传入数组和数组长度，输出从小到大排序好的元素。
    先遍历外层元素，每次遍历外层元素时，将外层访问元素的后一个元素保存到中间变量temp，
    内层从外层访问元素开始向前遍历。
    每次比较内层遍历的元素和中间变量的大小，如果中间变量比它小，则将它向后移动一个位置，
    一直到遍历的元素大于等于中间变量，终止内层遍历，并将中间变量赋值给最后一个移动元素原来所在位置。
    最终外层遍历完成后，数组有序。*/
// template <typename T>
// void insertSort(T arr[], int n){  
//     // *** 这里不用返回值，因为数组排序后在外部已经发生变化
//     for (int i = 0; i < n; i++){
//         // 内层遍历，移动元素。此处要防止数组越界
//         if (i + 1 < n){
//             int temp = arr[i+1];  
//             int j;  // 用于记录内层访问的元素位置
//             // for (int j = i; j >= 0; j--){
//             for (j = i; j >= 0; j--){
//                 if (temp < arr[j])
//                     arr[j+1] = arr[j];
//             }
//             // 内层遍历移动完成后，将内层最开始的元素(保存在temp中)赋值给最后一次移动的元素位置
//             arr[j] = temp;
//         }
//     }
//     return;
// }


template <typename T>
void insertSort(T arr[], int n){  
    // *** 这里不用返回值，因为数组排序后在外部已经发生变化
    for (int i = 1; i <= n-1; i++){
        // 内层遍历，向前移动元素
        int temp = arr[i];  
        int j;  // 用于记录内层访问的元素位置

        // #####如果将temp < arr[j-1]这个语句放在for循环{}内，即使j个元素比它前面的元素大，
        // j--依然会执行一次，arr[j] = temp;也会执行一次，此时temp就赋值给了j的前面一个元素，
        // 最终不能正确排序
        // for (j = i; j > 0; j--)
        //     if (temp < arr[j-1])
        //         arr[j] = arr[j-1];
        
        // #####将temp < arr[j-1]这个语句放在for循环的条件判断内，如果j个元素比它前面的元素大，
        // 不会执行循环体，j的值不会变化，后面执行arr[j] = temp;后，j个元素依然是它本身
        // for (j = i; j > 0 && temp < arr[j-1]; j--)
        //     arr[j] = arr[j-1];
        for (j = i-1; j >= 0 && temp < arr[j]; j--)
            arr[j+1] = arr[j];

        // 内层遍历移动完成后，如果有元素移动了，将内层最开始的元素
        // (保存在temp中)赋值给最后一次移动的元素位置
        arr[j+1] = temp;
    }
    return;
}

#endif

