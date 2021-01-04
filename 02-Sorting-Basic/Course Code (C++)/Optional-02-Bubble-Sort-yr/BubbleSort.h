#ifndef _BUBBLESORT_H
#define _BUBBLESORT_H


/*  传入数组和数组长度，输出从小到大排序好的元素。
    外层遍历n次，假设当前外层遍历次数为k(k范围为[0, n-1])，内层每次遍历下标[1, n-k-1]。
    内层每次遍历的元素与它前面一个元素比较，如果比前面的元素小，交换它们位置。
    当内层一次遍历完成后，没有排好序的元素中最大的元素会向下(向后)移动到n-k-1的位置。
    当外层遍历完成后，数组排序完成。
*/
// // 错误版本
// template <typename T>
// void bubbleSort(T arr[], int n){  
//     for (int k = 0; k < n; k++){
//         // 内层遍历[1, n-k)下标元素，交换元素位置
//         for (int j = 1; j < n-k; k++){
//             if (arr[j] < arr[j-1])
//                 swap(arr[j], arr[j-1]);
//         }                        
//     }
//     return;
// }


// // 版本一
// template <typename T>
// void bubbleSort(T arr[], int n){  
//     for (int k = 0; k <= n-2; k++){
//         // 内层遍历[1, n-k-1]下标元素，交换元素位置
//         for (int i = 1; i <= n-k-1; i++){
//             if (arr[i] < arr[i-1])
//                 swap(arr[i], arr[i-1]);
//         }                        
//     }
//     return;
// }


// 优化版本
template <typename T>
void bubbleSort(T arr[], int n){  
    for (int k = 0; k <= n-2; k++){
        bool isSwaped = false;  // 用于表示此次外层循环中是否有元素交换
        // 内层遍历[1, n-k-1]下标元素，交换元素位置
        for (int i = 1; i <= n-k-1; i++){
            if (arr[i] < arr[i-1]){
                swap(arr[i], arr[i-1]);
                isSwaped = true;
            }
        }
        if (isSwaped == false)
            return;  // 如果此次外层循环没有元素交换，终止排序                        
    }
    return;
}

#endif
