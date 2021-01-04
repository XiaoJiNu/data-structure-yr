#ifndef _02_Max_Heap_Class_Basice_yr_MaxHeap_h
#define _02_Max_Heap_Class_Basice_yr_MaxHeap_h

#include <utility>
#include <assert.h>

using std::swap;

template <typename ItemType>
class MaxHeap{
private:
    int capacity;         // 指定大顶堆的容量，即大顶堆最多有多少元素
    ItemType *arrayData;  // 定义一个数组用于存储所有元素，它的元素个数为大顶堆容量加1
    int count;            // 统计当前大顶堆拥有的元素个数

    // 将第k个元素进行上移操作，使完全二叉树保持大顶堆的性质
    void shiftUp(int k){
        // 当插入元素到达根节点或者它小于等于父节点时才终止上移操作
        // ### 没有到达根节点且它大于父节点时进行上移操作
        // while (k > 1 && arrayData[k] <= arrayData[k/2]){
        while (k > 1 && arrayData[k] > arrayData[k/2]){
            swap(arrayData[k], arrayData[k/2]);
            k = k/2;
        }
        
        return;
    }

    // 将第k个元素进行下移操作，使完全二叉树保持大顶堆的性质
    void shiftDown(int k){
        // 当节点没有子节点或者节点的值大于等于最大子节点时终止下移操作
        // 反之，如果节点有子节点且小于其中最大的节点，进行下移操作
        // ### 大于等于最大子节点这个条件在while条件中不好判断，
        // ### 所以在循环里面进行判断，满足条件break即可
        // 2*k 是k节点的左子节点序号，如果它小于等于count，证明左子节点存在
        while (2*k <= count ){
            // 如果k节点大于子节点中最大节点，将k节点与最大的节点交换即可，
            // 子节点中最大节点序号用j保存
            int j = 2*k;  
            // ### 如果右子节点存在且比左子节点大，令j为右子节点序号，需要判断
            // 2*k + 1 <= count，防止数组越界
            if (2*k + 1 <= count && arrayData[2*k] < arrayData[2*k + 1])
                j = 2*k + 1;  
            
            // 如果k节点比子节点中最大节点小，将它们交换位置
            if (arrayData[k] < arrayData[j]){
                swap(arrayData[k], arrayData[j]);
                k = j;  // 将k更换为交换的位置
            }
            else{
                break;  // 当k节点大于等于最大子节点时，终止下移
            }
        }
        
        return;
    }
    
public:
    MaxHeap(int maxCapacity){
        capacity = maxCapacity;
        arrayData = new ItemType[capacity + 1];  // 堆的元素从数组下标1开始，所以数组容量要加1
        count = 0;                               // 开始大顶堆没有元素
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

    // 插入一个元素
    void insert(ItemType newItem){
        // 将插入元素放入数组末尾
        assert(count + 1 <= capacity);  // 插入元素后数组不能越界
        arrayData[count + 1] = newItem;
        count ++;                       // 插入元素后count应该加1

        // 将元素上移
        // ### 前面count已经加1了，这里不能再加1
        // shiftUp(count + 1);
        shiftUp(count);

        return;
    }

    // 从堆中提取最大元素，然后进行下移操作
    ItemType extractMax(){
        // 这里是否需要判断堆中是否还有元素，即count > 0 ？？？ 答：需要
        assert(count > 0);
        ItemType maxItem = arrayData[1];  // 取出最大元素
        arrayData[1] = arrayData[count];  // 将末尾元素放到堆顶，即数组第一个元素
        count --;                         // 堆顶元素数量-1

        shiftDown(1);                     // 此时末尾元素处于堆顶，对它进行下移操作

        return maxItem;
    }

    ItemType getMax(){
        assert(count > 0);
        return arrayData[1];
    }

};

#endif