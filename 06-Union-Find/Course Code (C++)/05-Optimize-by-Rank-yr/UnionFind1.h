#ifndef _02_QIUCK_FIND_YR_UNIONFIND_H
#define _02_QIUCK_FIND_YR_UNIONFIND_H

#include <iostream>
#include <cassert>

namespace UF1{
    class UnionFind{
    private:
        int* idArray;  // 定义一个存储元素的数组
        int count;     // 记录元素个数

    public:
        UnionFind(int n){
            // 给数组赋值
            idArray = new int[n];
            for(int i = 0; i < n; i++)
                idArray[i] = i;  // 开始时每个元素的id都不相同
            
            count = n;
        }

        ~UnionFind(){ 
            delete[] idArray;  // 删除由new生成的数组
        }

        // 合并操作，将元素p,q对应的元素变成同样的id
        void unionElements(int p, int q){
            assert(0 <= p < count && 0 <= q < count);
            if (idArray[p] == idArray[q])
                return;  // 如果p,q本身id相同，则终止函数
            else{
                // 遍历所有元素，将与元素p的id相同的元素的id变成q的id
                for (int i = 0; i < count; i++){
                    if (idArray[i]==idArray[p])
                        idArray[i] = idArray[q];
                // return;  // ### 终止语句还能放在此处，否则只循环一次就结束了
                }
                return;  // 终止合并
            }
        }

        // 查找操作，查找元素p的id
        int find(int p){
            assert(0 <= p < count);
            int pID = idArray[p];
            return pID;
        }

        // 判断p,q元素是否连接
        bool isConnected(int p, int q){
            assert(0 <= p < count && 0 <= q < count);
            return (idArray[p] == idArray[q]);
        }
    };
} // namespace UF

#endif