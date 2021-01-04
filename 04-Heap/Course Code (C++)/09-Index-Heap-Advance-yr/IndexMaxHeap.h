#ifndef _08_INDEX_HEAP_YR_INDEX_HEAP_H
#define _08_INDEX_HEAP_YR_INDEX_HEAP_H

#include <cassert>
#include <algorithm>
#include <iostream>

using std::cout;
using std::swap;
using std::endl;

template <typename ItemType>
class IndexMaxHeap{
private:
    int capacity;    // 堆的容量
    int *indexes;    // 存储堆每个节点在data数组中的下标
    ItemType *data;  // 存储堆每个节点的实际元素值
    int *rev;        // 存储data下标在indexes中的下标
    int count;       // 记录堆的实际元素个数


    void shiftUp(int k){
        // 比较节点k与它的父节点对应data中的数据大小，如果节点k对应data的值比它的父节点
        // 对应data的值大，交换indexes中它们的值。直到k小于等于父节点或者到达根节点
        while (k > 1 && data[indexes[k]] > data[indexes[k/2]]){
            swap(indexes[k], indexes[k/2]);
            swap(rev[indexes[k]], rev[indexes[k/2]]);  // indexes交换元素后rev也要交换元素
            // ### 每次交换后k的值也要改变 !!!
            k = k/2;
        }

        return;
    }

    void shiftDown(int k){
        // 比较节点k在data中与它的子节点在data中最大值的大小，k节点小于节点最大值，
        // 交换它们在indexes中的值。直到k节点没有子节点(2*k < count)或者它大于等于子节点最大值
        while (2*k <= count){
            // ### j忘记写类型了
            int j = 2*k;  // j用于存储子节点最大值的序号
            // 如果右子节点存在且比左子节点大，则j存储右子节点序号
            if(2*k + 1 <= count && data[indexes[2*k+1]] > data[indexes[2*k]])
                j = 2*k + 1;
            // 如果k节点的值比子节点最大值小，交换indexes中它们的下标
            // ### 
            // if(data[indexes[k]] > data[indexes[j]])
            if(data[indexes[k]] < data[indexes[j]]){
                swap(indexes[k], indexes[j]);
                swap(rev[indexes[k]], rev[indexes[j]]);
                // ### 每次交换后k的值也要改变 ###
                k = j;
            }
            // ###
            else
                break;  // 当节点k的值大于或者等于子节点中最大值，终止
        }
        
        return;
    }

public:
    IndexMaxHeap(int capa){
        // 堆最多有capacity个元素，但是序号从1开始，所以indexes数组有capacity+1个元素
        indexes = new int[capa + 1];      
        data = new ItemType[capa + 1];  // 初始化为默认初始值
        rev = new int[capa + 1];        // 存储data下标在indexes中下标
        capacity = capa;
        count = 0;
    }

    ~IndexMaxHeap(){
        delete[] indexes;
        delete[] data;
        delete[] rev;
    }

    // 检查堆中的节点i是否已经有元素
    bool contain(int i){
        // 开始rev中的元素全部为0，表示堆中没有元素，如果i在[1, count]范围内或者rev[i] != 0，
        // 或者indexes[i] != 0，表示堆中已经有元素
        // assert(1 <= i <= count);
        if (rev[i] != 0)
            return true;
        else
            return false;
    }

    // 插入下标为i(外部数组下标i)的元素item
    void insert(int i, ItemType item){
        // ### assert( 0 <= i <= capacity );     // data数组不能越界
        assert( 1 <= i+1 <= capacity ); 
        assert( count + 1 <= capacity );  // index的元素个数不能越界

        // 需要判断堆中节点i+1是否已经有元素了，如果有则不能插入
        assert(!contain(i+1));

        data[i+1] = item;                 // 下标为i的元素存储在data的下标为i+1的位置
        indexes[count+1] = i+1;           // index增加一个元素，它的值就是item在data中下标
        rev[i+1] = count + 1;             // 表示data的下标i+1保存在indexes的下标count+1中
        count += 1;                       // 此时index元素个数加1

        // 对堆中节点count进行shiftUp操作，使index数组对应的data中的元素保持堆的结构
        shiftUp(count);
    }

    // 从最大索引堆中取出堆顶元素, 即索引堆中所存储的最大数据
    ItemType extractMax(){
        assert(count > 0);  // 堆不为空才能提取最大值
        ItemType maxValue = data[indexes[1]];
        swap(indexes[1], indexes[count]);
        swap(rev[indexes[1]], rev[indexes[count]]);  // 每次indexes交换时rev也要交换
        count --; 

        shiftDown(1);
        return maxValue;
    }

    // 从最大索引堆中取出堆顶元素的索引
    ItemType extractMaxIndex(){
        // ### data数组索引比外部数组索引多1，因为索引0没有在堆中
        int maxValueIndex = indexes[1] -1 ;
        swap(indexes[1], indexes[count]);
        swap(rev[indexes[1]], rev[indexes[count]]);
        count --;

        shiftDown(1);
        return maxValueIndex;
    }

    bool isEmpty(){
        return count == 0;  // 如果count不为0则说明不为空
    }

    // 返回索引堆中的元素个数
    int size(){
        return count;
    }

    // 获取堆中最大元素存储的数据
    ItemType getMax(){
        assert(count > 0);
        return data[indexes[1]];
    }

    // 获取最大索引堆中的堆顶元素的索引(外部数组索引)
    int getMaxIndex(){
        assert(count > 0);
        return indexes[1] -1;
    }

    // 获取最大索引堆中索引为i的元素(外部数组索引为i)
    ItemType getItem(int i){
        assert(i+1 <= count);
        // 外部数组索引为i，则在堆中存储的data数组索引为i+1
        return data[i+1];
    }

    // 将最大索引堆中索引为i(即外部数组索引为i)的元素修改为newItem
    void change(int i, ItemType newItem){
        // 外部数组索引为i，在data数组中索引为i+1
        assert(1 <= i+1 <= count);
        data[i+1] = newItem;
        // 由于indexes[i+1]对应data[i+1]的值发生改变，为了使indexes数组
        // 保持堆结构，需要对indexes中保存下标i+1的节点进行上移或者下移操作
        // ### for (int k = 0; k < count; k++){
        // for (int k = 1; k <= count; k++){
        //     if (indexes[k] == i+1){
        //         shiftUp(k);
        //         shiftDown(k);
        //     }   
        // }
        // 此时直接在rev中找到i+1这个下标存储在indexes中的下标即可
        int k = rev[i+1];  // data的下标i+1存储在数组indexes的下标rev[i+1]=k中
        shiftUp(k);        // 对堆的节点k进行上移或者下移
        shiftDown(k);
    }

    // 输出indexes数组和data数组
    void showIndexesData(){
        for (int i = 1; i <= count; i++)
            cout << indexes[i] << ":" << data[indexes[i]] << endl;

        for (int i = 1; i <= count; i++)
            cout << data[i] << " ";
        
        cout << endl;

    }

    // 测试索引堆中的索引数组index和反向数组reverse
    // 注意:这个测试在向堆中插入元素以后, 不进行extract操作有效
    bool testIndexesAndReverseIndexes(){

        int *copyIndexes = new int[count+1];
        int *copyReverseIndexes = new int[count+1];

        for( int i = 0 ; i <= count ; i ++ ){
            copyIndexes[i] = indexes[i];
            copyReverseIndexes[i] = rev[i];
        }

        copyIndexes[0] = copyReverseIndexes[0] = 0;
        std::sort(copyIndexes, copyIndexes + count + 1);
        std::sort(copyReverseIndexes, copyReverseIndexes + count + 1);

        // 在对索引堆中的索引和反向索引进行排序后,
        // 两个数组都应该正好是1...count这count个索引
        bool res = true;
        for( int i = 1 ; i <= count ; i ++ )
            if( copyIndexes[i-1] + 1 != copyIndexes[i] ||
                    copyReverseIndexes[i-1] + 1 != copyReverseIndexes[i] ){
                res = false;
                break;
            }

        delete[] copyIndexes;
        delete[] copyReverseIndexes;

        if( !res ){
            cout<<"Error!"<<endl;
            return false;
        }

        for( int i = 1 ; i <= count ; i ++ )
            if( rev[ indexes[i] ] != i ){
                cout<<"Error 2"<<endl;
                return false;
            }

        return true;
    }
    
};
 

#endif