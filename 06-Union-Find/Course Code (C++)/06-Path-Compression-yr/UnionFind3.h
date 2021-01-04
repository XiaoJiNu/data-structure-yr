#ifndef _03_QIUCK_FIND_YR_UNIONFIND3_H
#define _03_QIUCK_FIND_YR_UNIONFIND3_H

#include <iostream>
#include <cassert>

namespace UF3{
    class UnionFind{
    private:
        int* parent;    // 定义一个存储父亲节点的数组
        int* itemSize;  // 保存每个节点对应根节点连接的所有节点的数量
        int count;      // 记录元素个数

    public:
        UnionFind(int n){
            // 给数组赋值
            parent = new int[n];
            itemSize = new int[n];
            for(int i = 0; i < n; i++){
                parent[i] = i;    // 开始时每个元素节点都指向自身
                itemSize[i] = 1;  // 开始时每个元素的根节点是它本身，只有一个节点
            }
                
            count = n;
        }

        ~UnionFind(){ 
            delete[] parent;  // 删除由new生成的数组
            delete[] itemSize; 
        }

        // 查找操作，查找元素p的根节点，并返回根节点
        int find(int p){
            assert(0 <= p < count);
            // 如果当前节点的父节点不是它本身，则这个节点不是根节点
            // 否则就找到了根节点
            while (p != parent[p])
                p = parent[p];  // 沿着p的父节点向着根节点查找
            return p;
        }

        // 合并操作，元素p的根节点指向q的根节点
        void unionElements(int p, int q){
            assert(0 <= p < count && 0 <= q < count);
            int pRoot = find(p);
            int qRoot = find(q);

            if (pRoot == qRoot)
                return;  // 如果p,q根节点相同，则终止函数
            else{
                // 将元素少的节点的根指向元素多的节点指向的根
                // 同时改变被指向的根节点连接的元素数量
                if (itemSize[pRoot] < itemSize[qRoot]){
                    parent[pRoot] = qRoot;
                    itemSize[qRoot] += itemSize[pRoot];  
                }
                else{
                    parent[qRoot] = pRoot;
                    itemSize[pRoot] += itemSize[qRoot];
                }
            }
        }

        // 判断p,q元素是否连接
        bool isConnected(int p, int q){
            assert(0 <= p < count && 0 <= q < count);
            return (find(p) == find(q));
        }
    };
} // namespace UF

#endif