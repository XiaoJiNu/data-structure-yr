#ifndef _02_QIUCK_FIND_YR_UNIONFIND2_H
#define _02_QIUCK_FIND_YR_UNIONFIND2_H

#include <iostream>
#include <cassert>

namespace UF2{
    class UnionFind{
    private:
        int* parent;   // 定义一个存储父亲节点的数组
        int count;     // 记录元素个数

    public:
        UnionFind(int n){
            // 给数组赋值
            parent = new int[n];
            for(int i = 0; i < n; i++)
                parent[i] = i;  // 开始时每个元素节点都指向自身
            count = n;
        }

        ~UnionFind(){ 
            delete[] parent;  // 删除由new生成的数组
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
            else
            // ### 错误，应该是p的根节点指向另一个q的根节点，不是p的父节点指向q的根节点
            //    parent[p] = qRoot;  
               parent[pRoot] = qRoot;
        }

        // 判断p,q元素是否连接
        bool isConnected(int p, int q){
            assert(0 <= p < count && 0 <= q < count);
            return (find(p) == find(q));
        }
    };
} // namespace UF

#endif