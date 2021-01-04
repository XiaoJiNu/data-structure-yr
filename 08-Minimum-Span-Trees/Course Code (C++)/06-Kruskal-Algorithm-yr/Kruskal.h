#ifndef _06_KRUSKAL_ALGORITHM_YR_H
#define _06_KRUSKAL_ALGORITHM_YR_H

#include <vector>

#include "MinHeap.h"
#include "UF.h"
#include "Edge.h"

template <typename Graph, typename Weight>
class Kruskal{
private:
    // Graph g;
    vector<Edge<Weight>> mst;
    MinHeap<Edge<Weight>> pq;
    UnionFind uf;
    Weight weightSum;

public:
    // ### pq, uf是自定义的类型，并且没有默认构造函数，只能用参数列表方式进行初始化，不能用赋值方式
    Kruskal(Graph g): pq(MinHeap<Edge<Weight>>(g.E())), uf(UnionFind(g.V())){
        // g = graph;
        // ### 开始没有对各个私有变量初始化
        mst = vector<Edge<Weight>>();
        // MinHeap<Edge<Weight>> pq(g.E());
        // pq = MinHeap<Edge<Weight>>(g.E());
        // UnionFind uf(g.V());  
        // ### no matching function for call to ‘UnionFind::UnionFind()’
        // uf = UnionFind(g.V());  

        // 遍历所有的边，将边放入最小堆中
        for (int i = 0; i < g.V(); i++){
            // 迭代每个顶点的邻边
            typename Graph::adjIterator iter(g, i);
            // ### 每次迭代没有对adjEdge赋值，出现错误
            // for (Edge<Weight>* adjEdge = iter.begin(); !iter.end(); iter.next()){
            for (Edge<Weight>* adjEdge = iter.begin(); !iter.end(); adjEdge = iter.next()){
                // 由于无向图一条边会遍历两次，但是这里只需要向堆中添加一次
                if (adjEdge->getA() < adjEdge->getB())  
                    pq.insert(*adjEdge);
            }
        }

        // 依次在最小堆中取出最小的边，只要不形成环，则这条边就是最小生成树的边
        // 这里应该是且的关系而不是或的关系
        // while (!pq.isEmpty() || mst.size() <= g.V() - 1){  
        while (!pq.isEmpty() && mst.size() <= g.V() - 1){
            Edge<Weight> minEdge = pq.extractMin();
            if (uf.isConnected(minEdge.getA(), minEdge.getB()))
                continue;
            mst.push_back(minEdge);
            // 查找这两条边的id，将它们合并成一个集合
            // aID = uf.find(minEdge.getA());  
            // bID = uf.find(minEdge.getB());
            uf.unionElements(minEdge.getA(), minEdge.getB());
        }  

        // 求最小生成树的和
        weightSum = mst[0].getWeight();
        for (int i = 1; i < mst.size(); i++){
            weightSum += mst[i].getWeight();
        }
    }

    ~Kruskal(){}

    // 返回最小生成树
    vector<Edge<Weight>> minGenTreeEdges(){
        return mst;
    }

    // 返回最小生成树的权值的和
    Weight minGenTreeValue(){
        return weightSum;
    }
};


#endif
