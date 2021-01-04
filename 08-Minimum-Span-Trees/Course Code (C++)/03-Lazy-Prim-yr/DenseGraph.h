#ifndef _01_WEIGHTED_GRAPH_YR_DENSEGRAPH_H
#define _01_WEIGHTED_GRAPH_YR_DENSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

#include "Edge.h"
using namespace std;

template <typename Weight>
class DenseGraph{
private:
    int vertexNum, edgeNum;
    bool directed;  // 表示是否是有向边  
    vector<vector<Edge<Weight>*>> adjMatrix;

public:
    DenseGraph(int v, bool directed){
        assert(v >=0 );  // 保证节点数大于等于0
        vertexNum = v;
        edgeNum = 0;
        this -> directed = directed;
        // 正确写法1
        // adjMatrix = vector<vector<Edge<Weight>*>>(vertexNum, \
        //             vector<Edge<Weight>*>(vertexNum, nullptr));
        // 正确写法2
        adjMatrix = vector<vector<Edge<Weight>*>>(vertexNum, \
                    vector<Edge<Weight>*>(vertexNum));
    }

    ~DenseGraph(){
        // 对于分配了内存的元素进行删除
        for (int i = 0; i < vertexNum; i++){
            for (int j = 0; j < vertexNum; j++){
                if (adjMatrix[i][j] != nullptr){
                    delete adjMatrix[i][j];  
                }
            }
        }
    }

    int V(){ return vertexNum;}

    int E(){ return edgeNum;}

    // 判断是否有边
    bool hasEdge(int a, int b){
        assert(0 <= a < vertexNum);
        assert(0 <= b < vertexNum);
        // 如果adjMatrix[a][b]为空指针则返回false，否则返回true
        return adjMatrix[a][b] != nullptr;
    }

    // 传入两个顶点以及权重，构建一条边
    void addEdge(int a, int b, Weight w){
        assert(0 <= a < vertexNum);
        assert(0 <= b < vertexNum);
        // 如果a,b已经有边，删除已经存在的边
        if (hasEdge(a, b)) {
            delete adjMatrix[a][b];  
            // ### 对于无向边，需要删除存储在[b][a]下标的边
            if (a != b && !directed){
                delete adjMatrix[b][a];
            }
            // ### 删除一条边需将记录边的变量-1
            vertexNum --;
        }
        // 添加边
        adjMatrix[a][b] = new Edge<Weight>(a, b, w);                           
        // ### 如果是无向图，再添加另一个元素，注意a!=b条件
        if (a != b && !directed){
            adjMatrix[b][a] = new Edge<Weight>(b, a, w);
        }
        // ### 开始写成了vertexNum ++;
        edgeNum ++;
    }

    // 显示整个图的信息
    void show(){
        for (int i = 0; i < vertexNum; i++){
            for (int j = 0; j < vertexNum; j++){
                if (adjMatrix[i][j] != nullptr){
                    cout << adjMatrix[i][j] -> getWeight() << " ";
                }
                else{
                    cout << "null" << " ";
                }
            }
            cout << endl;
        }
    }

    // 传入一个图以及一个顶点，迭代这个顶点的邻边
    class adjIterator{
    private:
        DenseGraph &g;
        int vertex;
        int index; // 记录迭代的次数

    public:
        adjIterator(DenseGraph &graph, int v): g(graph){
            vertex = v;
            index = 0;
        }

        Edge<Weight>* begin(){
            // 邻接矩阵中的元素一定都有值，迭代一个顶点的邻边，需要
            // 判断一个元素是否有边，所以统一在next()处于更方便
            index = 0;  // 为了防止多次调用，每次调用令index=0;                                          
            return next();                                                     
        }

        Edge<Weight>* next(){
            // ### 这里不应该用index < vertexNum来判断，直接调用vertexNum是不合理的
            // for (; index < vertexNum; index++){
            for (; index < g.V(); index++){
                if (g.adjMatrix[vertex][index] != nullptr){
                    return g.adjMatrix[vertex][index];
                } 
            }
            // 如果没有找到边，返回空指针，此时由于index大于顶点数vertexNum，
            // 在外层调用时由于满足end()而终止，不会输出nullptr
            return nullptr;  
        }

        bool end(){
             // ### 这里不应该直接调用vertexNum，而应该用g.V()
            return index >= g.V();
        }
    };

};

                        
#endif