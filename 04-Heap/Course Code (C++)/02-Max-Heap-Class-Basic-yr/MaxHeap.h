#ifndef _02_Max_Heap_Class_Basice_yr_MaxHeap_h
#define _02_Max_Heap_Class_Basice_yr_MaxHeap_h

template <typename Item>
class MaxHeap{
private:
    int capacity;     // 指定大顶堆的容量，即大顶堆最多有多少元素
    Item *arrayData;  // 定义一个数组用于存储所有元素，它的元素个数为大顶堆容量加1
    int count;        // 统计当前大顶堆拥有的元素个数
    
public:
    MaxHeap(int maxCapacity){
        capacity = maxCapacity;
        arrayData = new Item[capacity + 1];  // 堆的元素从数组下标1开始，所以数组容量要加1
        count = 0;                           // 开始大顶堆没有元素
    }

    ~MaxHeap(){
        delete[] arrayData;
    }

    int size(){
        return count;  // 返回当前大顶堆的的元素数量
    }

    // 检测大顶堆是否为空
    bool isEmpty(){
        if (count == 0)
            return true;
        else
            return false;
    }

};

#endif