#include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include <cstdlib>
using namespace std;


// 遍历Sparse矩阵
void iterateSparseGrap(){
    int vertexNum = 2, edgeNum = 10;
    bool directed = false;
    SparseGraph g(vertexNum, edgeNum, directed);
    // 添加边
    for (size_t i = 0; i < edgeNum; i++){
        int a = rand() % vertexNum;
        int b = rand() % vertexNum;
        g.addEdge(a, b);
    }
    
    // 遍历所有顶点的邻边
    for (size_t i = 0; i < vertexNum; i++){
        cout << i << ":";
        SparseGraph::Iterator graphIter(g, i);
        for (int w=graphIter.begin(); !graphIter.end(); w=graphIter.next()){
            cout << w << " ";
        }
        cout << endl;
    }
    return;
}


// 遍历稠密图
void iterateDenseGraph(){
    int vertexNum = 5, edgeNum = 2;
    bool directed = false;

    // 创建一个图并添加边
    DenseGraph g(vertexNum, edgeNum, directed);
    for (size_t i = 0; i < edgeNum; i++){
        int v = rand() % vertexNum;
        int w = rand() % vertexNum;
        g.addEdge(v, w);
    }
    

    for (size_t v = 0; v < vertexNum; v++){
        DenseGraph::Iterator iter(g, v);
        cout << v << ": ";
        for (size_t w = iter.begin(); !iter.end(); w = iter.next()){
            cout << w << " ";
        }
        cout << endl;
    }
    
    return;
}

 
int main()
{
    // iterateSparseGrap();
    iterateDenseGraph();

    return 0;
}