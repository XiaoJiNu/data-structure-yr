#ifndef _DenseGraph_H_
#define _DenseGraph_H_

#include <vector>
#include <assert.h>
#include <iostream>

using std::vector;
using std::cout;

class DenseGraph{
private:
    int vertexNum, edgeNum;
    bool directed;
    vector<vector<bool>> adjMatrix;
public:
    DenseGraph(int n, int m, bool directed);
    ~DenseGraph();
    void addEdge(int v, int w);
    bool hasEdge(int v, int w);

    class Iterator{
    private:
        DenseGraph &graph;  // 为什么不对graph进行初始化？
        int searchVertex;
        int index;
    public:
        // 引用或者是具有非默认构造函数的对象或者是常量，只能在构造列表进行初始化
        Iterator(DenseGraph &g, int v):graph(g){
            this->searchVertex = v;
            this->index = 0;
        }

        ~Iterator(){}

        // void iteratorGraph(){
        //     for (size_t i = 0; i < graph.adjMatrix[searchVertex].size(); i++){
        //         if (graph.adjMatrix[searchVertex][i]==true) 
        //             cout << graph.adjMatrix[searchVertex][i] << "";
        //     }
        //     cout << std::endl;
        // }
        int begin(){
            index = -1;
            return next();
        }

        int next(){
            // if (index < graph.vertexNum && graph.adjMatrix[searchVertex][index]==true){
            //     return index;
            // } 
            // 每次调用next都将在adjMatrix[v]中从上次的index开始寻找与v有边的第一个顶点，返回该顶点下标
            for (index ++; index < graph.vertexNum; index ++){
                if (graph.adjMatrix[searchVertex][index]==true) 
                    return index;
            }
            
            // 1：为什么不返回-1也可以？？
            // 因为当index越界时，在main函数中对Iterator的遍历已经终止，此时将不会再调用next()，
            // 所以不会出现返回-1的情况。但是为了程序的逻辑完整，应该加上返回-1
            // 2：如果当前顶点与searchVertex没有边，返回-1。但是返回-1是为什么没有输出-1？
            // 当前面的for循环结束时，遍历完了adjMatrix[v]这一行才会到return -1这一行，
            // 此时index将越界，所以终止遍历searchVertex邻接点，所以-1不会输出
            return -1; 
        }

        int end(){
            return index >= graph.vertexNum;
        }
    };
};

DenseGraph::DenseGraph(int n, int m, bool directed){
    this->vertexNum = n;
    this->edgeNum = m;
    this->directed = directed;
    this->adjMatrix = vector<vector<bool>>(this->vertexNum, 
                      vector<bool>(this->vertexNum));
}

DenseGraph::~DenseGraph(){}

void DenseGraph::addEdge(int v, int w){
    // 判断是否超过节点数量
    assert(0<v<vertexNum);
    assert(0<w<edgeNum);
    if (hasEdge(v, w)) return;

    adjMatrix[v][w] = true;
    if (!directed){
        adjMatrix[w][v] = true;
    }

    return;
}

bool DenseGraph::hasEdge(int v, int w){
    assert(0<v<vertexNum);
    assert(0<w<vertexNum);

    return adjMatrix[v][w];
}

#endif
