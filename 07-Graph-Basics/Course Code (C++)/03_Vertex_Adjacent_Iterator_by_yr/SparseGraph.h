#ifndef _SparseGraph_H_
#define _SparseGraph_H_

#include <vector>
#include <assert.h>
using std::vector;


// 邻接表
class SparseGraph{
private:
    /* data */
    int vertexNum, edgeNum;
    bool directed;
    // 这里的二维数组的每一行代表一个顶点的相邻接点，行号就是顶点号，
    // 每一行存储的元素就是这个顶点相邻顶点的等号。并没有用链表节点来存储顶点数据
    vector<vector<int>> adjList;

public:
    SparseGraph(int vertexNum, int edgeNum, bool directed);
    ~SparseGraph();
    void addEdge(int a, int b);
    class Iterator{
    private:
        /* data */
        SparseGraph &graph;
        int search_vertex;
        int index;
        
    public:
        Iterator(SparseGraph &g, int a): graph(g){
            search_vertex = a;
            index = 0;
        }

        // ~Iterator(){}

        int begin(){
            index = 0;
            if (graph.adjList[search_vertex].size() > 0){
                // index++;
                return graph.adjList[search_vertex][index];
            }
            return -1; // 没有邻接点，返回-1
            // return index;
        }

        int next(){
            index++; 
            if (index < graph.adjList[search_vertex].size()){
                // index++; 此句应该放在if外面，防止index越界
                return graph.adjList[search_vertex][index];
            }
            return -1; // index越界，返回-1，在main函数循环中判断!end()时将终止遍历，所以不会输出-1
        }

        bool end(){
            return index >= graph.adjList[search_vertex].size();
        }
    };
};

SparseGraph::SparseGraph(int vertexNum, int edgeNum, bool directed){
    this->vertexNum = vertexNum;
    this->edgeNum = edgeNum;
    this->directed = directed;
    adjList = vector<vector<int>>(this->vertexNum, vector<int>());
}

SparseGraph::~SparseGraph(){
}

void SparseGraph::addEdge(int v, int w){
    assert(0 < v < vertexNum);
    assert(0 < w < vertexNum);
    adjList[v].push_back(w);
    // 如果是无向图且v不是自环边(自环边的话v=w，此时在前面已经push进向量了)
    // 此时没有判断前面的v,w是否已经有边了，因为如果遍历一次v的邻边，
    // 最坏的结果可能要遍历所有节点，造成时间复杂度过于复杂
    if (v!=w && !directed){
        adjList[w].push_back(v);
    }

    edgeNum++; // 统计边的数量
}

#endif