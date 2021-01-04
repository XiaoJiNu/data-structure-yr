#ifndef _QUICKSORT_H
#define _QUICKSORT_H

using namespace std;


template <typename T>
int _partition(T arr[], int L, int R){
    T temp = arr[L];  // 以arr[L]为分割标准
    int j = L;        // j为分界下标。初始时，j的左边元素个数为0，表示目前没有小于arr[L]的元素
    int i = L+1;      // 初始时，i=L+1，然后i一直遍历到R，对每个元素进行判断

    for (; i <= R; i++){
        if (arr[i] < temp){        // 如果arr[i] < temp，则将arr[i]放到分界点左边先对j加1
            j++;                   // ，此时j左边的元素(即小于temp的元素)增加了1个交换arr[i]
            swap(arr[i], arr[j]);  // 和arr[j]，此时arr[j]的元素变成了arr[i],小于temp
        }
    }
    
    swap(arr[j], arr[L]);          // 当i遍历完arr后，此时arr[j] < temp=arr[L]，交换
                                   // arr[j]和arr[L]，则下标j的左边所有元素都小于temp
    return j;                      // 返回分界下标j，在递归中继续排序j的左右两边元素 
}


template <typename T>
void _qickSort(T arr[], int L, int R){
    // 递归函数，对arr[L]到arr[R]范围内的元素进行partition操作，partition操作
    // 返回partition后的分界点,同时使arr[L]到arr[p]范围内元素全部小于开始的arr[L]元素，
    // arr[p+1]到arr[R]范围内元素全部大于等于arr[L]
    if (L >= R)
        return;                     // 递归到最底层，此时L=R，终止递归
    
    int p = _partition(arr, L, R);  // partition后会返回partition临界点下标
    _qickSort(arr, L, p-1);
    _qickSort(arr, p+1, R);

    return;
}


template <typename T>
void qickSort(T arr[], int n){
    _qickSort(arr, 0, n-1);

    return;
}

#endif