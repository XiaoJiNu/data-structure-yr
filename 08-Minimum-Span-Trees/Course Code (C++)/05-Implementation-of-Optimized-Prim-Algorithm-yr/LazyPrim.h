#ifndef _03_LAZY_PRIM_YR_LAZYPRIM_H_
#define _03_LAZY_PRIM_YR_LAZYPRIM_H_

#include <iostream>
#include <vector>

#include "SparseGraph.h"
#include "DenseGraph.h"
#include "Edge.h"
#include "MinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class LazyPrim{
private:
    Graph &g;
    bool *marked;                     // 记录一个顶点是否被访问过
    MinHeap<Edge<Weight>> pq;         // 用最小堆来保存备选边，从其中找到权值最小边
    vector<Edge<Weight>> minGenTree;  // 保存最小生成树所有的边    
    Weight minResult;                 // 保存最小生成树的权值和

    // 将当前顶点标记为已经访问，同时将这个顶点的邻边中属于横切边的边存入最小堆
    void visit(int i){
        // ### 开始没有判断异常
        assert(marked[i] == false);
        marked[i] = true;
        typename Graph::adjIterator adjIter(g, i);                             
        // ### 这里在for循环的第三个位置不能再定义Edge<Weight> *adjEdge，前面已经定义了
        // for (Edge<Weight> *adjEdge = adjIter.begin(); !adjIter.end(); 
        //      Edge<Weight> *adjEdge = adjIter.next()) {
        for (Edge<Weight> *adjEdge = adjIter.begin(); !adjIter.end(); adjEdge = adjIter.next()) {
            // 如果邻接边的另一个顶点没有访问过，证明是横切边，放入最小堆。否则不放入最小堆
            if (marked[adjEdge->other(i)] == false) {
                pq.insert(*adjEdge);
            }
        }
    }
                                                                                    
public:
    /*
    // ### no matching function for call to ‘MinHeap<Edge<float> >::MinHeap()’
       在构造函数中没有对最小堆pq进行初始化，报错。因为它不是一个内置类型，同时了没有写一
       个默认构造函数MinHeap()，编译器无法为它给定一个内类初始值。最小堆的构造函数需要给定
       它所包含的最大节点数，这里为图的节点数量
       ### 初始化最小堆的时候，最小堆的容量应该是图的边的数量，因为所有的边都会放入最小堆中
       最坏的情况是最小堆中同时存储了所有边
    */
    LazyPrim(Graph &graph): g(graph), pq(MinHeap<Edge<Weight>>(g.E())) {
        marked = new bool[g.V()];
        // ### request for member ‘size’ in ‘((LazyPrim<Graph, Weight>*)this)->
        // LazyPrim<Graph, Weight>::marked’, which is of non-class type ‘bool*’gcc
        // 数组不能用size()求出长度，可以用sizeof(marked) / sizeof(marked[0])求，这里
        // 直接用g.V()也是它的长度
        // for (int i = 0; i < marked.size(); i++) 
        for (int i = 0; i < g.V(); i++) 
            marked[i] = false;
        // ###
        minGenTree.clear();


        /* 1 访问图的0节点
           2 在最小堆中提取权值最小横切边，直到最小堆为空 */
        visit(0);
        while (!pq.isEmpty()){
            Edge<Weight> minEdge = pq.extractMin();
            // 如果取出的最小边都访问过或者都没有访问过，它不是横切边
            if (marked[minEdge.getA()] == marked[minEdge.getB()]){
                continue;
            }
            else{
                minGenTree.push_back(minEdge);  // 将最小边放入最小生成树中
                // 继续访问横切边中没有访问的顶点，将它的邻边加入最小堆，进行下一次循环
                if (marked[minEdge.getA()] == false) 
                    visit(minEdge.getA());
                else 
                    visit(minEdge.getB());
            }
        }

        // 求最小生成树的权值的和，minResult必需先赋值为最小生成树的第一个元素，
        // 如果在minGenTreeValue()函数中进行计算，由于minResult的类型是自定义类型weight,
        // minResult是随机赋值，得到的结果不正确
        minResult = minGenTree[0].getWeight();
        for (int i = 1; i < minGenTree.size(); i++) {
            minResult += minGenTree[i].getWeight();
        } 
    }

    ~LazyPrim() {delete[] marked;}

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