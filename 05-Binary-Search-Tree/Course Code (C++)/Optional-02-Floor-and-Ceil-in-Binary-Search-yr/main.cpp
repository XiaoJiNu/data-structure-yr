#include <iostream>
#include <cassert>

using namespace std;


template <typename T>
int floor(T a[], int n, T target){
    assert(n > 0);

    // 在(left, right]范围内搜索target
    int left = -1, right = n-1;
    int mid = 0;  // mid为搜索范围内的中间下标，初始化为0

    // 在(left, right]范围内搜索target，直到left == right
    while(left < right){
        mid = left + (right - left + 1) / 2;  // 向上取整，为什么要向上取整？？
        // 当a[mid] == target时，依然在mid的左侧搜索，这样最终得到的left，right
        // 下标就在target元素左侧
        if (a[mid] >= target)
            right = mid - 1;  // right在搜索范围内，所以为mid - 1
        else
            left = mid;       // left不在搜索范围内，所以为mid        
    }

    // 终止查找时，left == right，如果此时a[right+1]==target则数组中有target，
    // 返回right+1。否则数组中没有target，只需返回比target小的元素的最大下标，即right
    if(0 <= right <= n-1 && a[right+1] == target)
        return right + 1;
    else
        return right;
}


template <typename T>
int ceil(T a[], int n, T target){
    // ### 
    assert(n > 0);
    // 搜索范围在[left, right)范围
    int left = 0, right = n;
    int mid = 0;  
    
    while (left < right){
        mid = left + (right - left) / 2;  // 向下取整，因为搜索范围在[left, right)？？
        // 如果a[mid]==target，依然在mid右侧范围搜索，这样最终得到的left, right在target的右侧
        if (a[mid] <= target)
            left = mid + 1;  // left在搜索范围，所以left = mid + 1
        else
            right = mid;     // right不在搜索范围
    }

    // 终止查找时，left==right且在target右侧，如果a[left]==target返回left-1，否则没有target，
    // 直接返回left即可
    if(0 <= left <= n-1 && a[left-1] == target)
        return left -1 ;
    else
        return left;
}


int main(){
    int a[] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 5, 5, 5, 6, 6, 6};
    int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < 8; i++){
        // 求出i在数组a中的floor下标
        int floorIndex = floor(a, n, i);
        cout << "floor index of index " << i << " is :" << floorIndex << endl;

        // 求出i在数组a中的ceil下标
        int ceilIndex = ceil(a, n, i);
        cout << "ceil index of index " << i << " is :" << ceilIndex << endl;
    }

    return 0;
}