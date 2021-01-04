#include <iostream>
#include <random>
#include "MaxHeap.h"

using namespace std;
using ItemType = int;

int main(){
    // 随机生成100个数，插入一个大顶堆
    int capacity = 100;
    MaxHeap<ItemType> pq(capacity);

    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, capacity - 1);
    for (int i = 0; i < capacity; i++){
        pq.insert(u(e));
    }
    
    // 创建一个数组用于存放从堆中取出的元素，数组中元素是有序的
    ItemType *orderedArray = new ItemType[capacity];
    for (int i = 0; i < capacity; i++){
        orderedArray[i] = pq.extractMax();
    }

    // 输出数组中的元素
    for (int i = 0; i < capacity; i++){
        cout << orderedArray[i] << " ";
    }
    cout << endl;

    return 0;
}
    
