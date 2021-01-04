#ifndef _03_LAZY_PRIM_YR_OptimPrim_H_
#define _03_LAZY_PRIM_YR_OptimPrim_H_

#include <iostream>
#include <vector>

#include "IndexMinHeap.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "Edge.h"
#include "MinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class OptimPrim{
private:
    Graph &g;
    bool *marked;                     // 记录一个顶点是否被访问过
    IndexMinHeap<Weight> indexPQ;     // 用最小索引堆来保存横切边，它将保存一个顶点以及这个顶点对应
                                      // 的最小横切边的权重。而lazy prim的最小堆将保存所有横切边
    vector<Edge<Weight>*> edgeTo;     // edgeTo这个vector的长度和顶点数一样，每个顶点
                                      // 保存的是它对应的最小边的指针，每次访问一个顶点
                                      // 时更新最小边，当找到最小横切边时，可以根据索引
                                      // 在edgeTo中找到这个最小横切边。它保存的元素和indexPQ中一样
    vector<Edge<Weight>> minGenTree;  // 保存最小生成树所有的边    
    Weight minResult;                 // 保存最小生成树的权值和

    // 将当前顶点标记为已经访问，同时将这个顶点的邻边中属于横切边的边存入最小堆，更新edgeTo
    void visit(int i){
        // ### 开始没有判断异常
        assert(marked[i] == false);
        marked[i] = true;
        typename Graph::adjIterator adjIter(g, i);                             
        for (Edge<Weight> *adjEdge = adjIter.begin(); !adjIter.end(); adjEdge = adjIter.next()) {
            // 如果邻接边的另一个顶点w没有访问过，证明是横切边，放入最小堆，
            // 否则不放入最小堆。同时会更新vector edgeTo
            int w = adjEdge -> other(i);   // 顶点i邻边顶点w
            if (marked[w] == false) {
                // 如果edgeTo中另一个顶点目前没有保存边，则将这个横切边放入edgeTo，同时将它放入最小堆
                if (edgeTo[w]==nullptr){
                    edgeTo[w] = adjEdge;
                    indexPQ.insert(w, adjEdge->getWeight());
                }
                // 如果edgeTo中另一个顶点有边且当前横切边比edgeTo中的边小，更新edgeTo中的边为当前边
                // 如果edgeTo中另一个顶点有边且当前横切边比edgeTo中的边大，则跳过这条边
                else if (edgeTo[w] != nullptr && *adjEdge < *edgeTo[w]){
                // else if (adjEdge->getWeight() < edgeTo[w]->getWeight()){
                    edgeTo[w] = adjEdge;
                    // ### 这里应该是用change而不是insert
                    // indexPQ.insert(w, adjEdge->getWeight());
                    indexPQ.change(w, adjEdge->getWeight());
                }
            }
        }
    }
                                                                                    
public:
    /* ### 初始化最小堆的时候，最小堆的容量应该是图的顶点的数量，它的index和edgeTo索引对应 */
    OptimPrim(Graph &graph): g(graph), indexPQ(IndexMinHeap<Weight>(g.V())) {
        marked = new bool[g.V()];
        for (int i = 0; i < g.V(); i++){
            marked[i] = false;
            // ### edgeTo这个vector开始并没有给定它的长度，
            // 所以这里不能直接用索引的方式进行初始化
            // edgeTo[i] = nullptr;
            edgeTo.push_back(nullptr);
        }
        // ###
        minGenTree.clear();

        /* 1 访问图的0节点
           2 在最小堆中提取权值最小横切边，直到最小堆为空 */
        visit(0);
        // 最坏的情况，indexPQ会存储所有的边E个，每次取最大元素，时间复杂度logV，所以时间复杂度为ElogV
        while (!indexPQ.isEmpty()){
            // 取出最小横切边的索引
            // ### lazy prim算法中取出的边有可能不是横切边，因为它是遍历顶点。
            //     但是优化的prim算法取出的一定是横切边，因为在visit中添加的是横切边
            int minEdgeIndex = indexPQ.extractMinIndex();
            // 在edgeTo中找到对应的横切边，然后将最小横切边放入结果中
            minGenTree.push_back(*edgeTo[minEdgeIndex]);
            visit(minEdgeIndex);
        }

        // 求最小生成树的权值的和，minResult必需先赋值为最小生成树的第一个元素，
        // 如果在minGenTreeValue()函数中进行计算，由于minResult的类型是自定义类型weight,
        // minResult是随机赋值，得到的结果不正确
        minResult = minGenTree[0].getWeight();
        for (int i = 1; i < minGenTree.size(); i++) {
            minResult += minGenTree[i].getWeight();
        } 
    }

    ~OptimPrim() {delete[] marked;}

    // 返回最小生成树的所有边
    vector<Edge<Weight>> minGenTreeEdges(){
        return minGenTree;
    }

    // 返回最小生成树的权值的和
    Weight minGenTreeValue(){
        // for (auto e : minGenTree)
        //     minResult += e.getWeight();
        return minResult;
    }
};

#endif