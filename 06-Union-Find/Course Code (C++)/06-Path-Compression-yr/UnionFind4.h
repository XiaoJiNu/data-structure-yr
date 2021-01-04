#ifndef _04_QIUCK_FIND_YR_UNIONFIND4_H
#define _04_QIUCK_FIND_YR_UNIONFIND4_H

#include <iostream>
#include <cassert>

namespace UF4{
    class UnionFind{
    private:
        int* parent;  // 定义一个存储父亲节点的数组
        int* rank;    // 保存每个节点对应根节点连接的所有节点的数量
        int count;    // 记录元素个数

    public:
        UnionFind(int n){
            // 给数组赋值
            parent = new int[n];
            rank = new int[n];
            for(int i = 0; i < n; i++){
                parent[i] = i;  // 开始时每个元素节点都指向自身
                rank[i] = 1;    // 开始时每个元素的根节点是它本身，高度为1
            }
                
            count = n;
        }

        ~UnionFind(){ 
            delete[] parent;  // 删除由new生成的数组
            delete[] rank;
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
                // 将节点所在树中高度低的节点的根指向高度高的节点指向的根
                // 此时不改变树的高度，因为树的高度不会发生改变
                if (rank[pRoot] < rank[qRoot])
                    parent[pRoot] = qRoot;
                else if (rank[pRoot] > rank[qRoot])
                    parent[qRoot] = pRoot;
                else{
                    // 高度一样时，随便指向哪个根节点都无所谓，但是高度要加1
                    parent[qRoot] = pRoot;
                    rank[pRoot] += 1;
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