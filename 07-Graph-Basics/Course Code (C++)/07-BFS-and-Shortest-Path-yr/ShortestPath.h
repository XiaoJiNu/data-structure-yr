#ifndef BFS_AND_SHORTEST_PATH_YR_SHORESTPATH_H
#define BFS_AND_SHORTEST_PATH_YR_SHORESTPATH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include "SparseGraph.h"
#include "DenseGraph.h"

using std::vector;
using std::queue;
using std::cout;
using std::endl;
using std::stack;


template <typename Graph> 
class ShortestPath{
private:
    Graph &graph;
    int source;           // 原点
    bool *visited;        // 记录每个节点是否已经访问
    int *from;            // 记录广度优先遍历中每个节点在上一层中相连的节点
    int *order;           // 记录每个节点距离原点的距离，也即所处的层数
    // int currentLayerNum;  // 用于记录深度优先遍历时当前节点的层数

    void bfs(int i){
        queue<int> bfsQueue;
        bfsQueue.push(i);
        // #####错误1：开始没有对原点的visited进行设置，导致出错#####
        visited[i] = true;
        order[i] = 0;  // 原点的序号为0
        while (!bfsQueue.empty()){
            int curVertex = bfsQueue.front();
            bfsQueue.pop();
            // #####错误3：调用模型类里面的类别，开始如下面这么写是错误的#####
            // typename Graph graph<>::adjIterator adjVertexIter(graph, curVertex);
            typename Graph::adjIterator adjVertexIter(graph, curVertex);
            for (int adjVertex = adjVertexIter.begin(); !adjVertexIter.end(); 
                 adjVertex = adjVertexIter.next()){
                if (!visited[adjVertex]){
                    bfsQueue.push(adjVertex);
                    // 维护当前结点信息
                    visited[adjVertex] = true;
                    from[adjVertex] = curVertex;
                    // order不是靠记录每个节点的所处的层数来得到的，而是利用每个节点上
                    // 一层的相连结点的层数+1得到
                    // order[adjVertex] = currentLayerNum;
                    order[adjVertex] = order[curVertex] + 1;
                }
            }
        }
        return;
    }

public:
    ShortestPath(Graph &g, int s): graph(g){
        // 初始化数据
        source = s;
        visited = new bool[graph.V()];
        from = new int[graph.V()];
        order = new int[graph.V()];
        for (int i = 0; i < graph.V(); i++){
            visited[i] = false;
            from[i] = -1;
            order[i] = 0;
        }
        

        // #####进行广度优先遍历，遍历过程中对visited,from,order进行相应修改#####
        // 如果图有多个commponent，可以用下面的代码来实现深度优先搜索
        // for (int i = 0; i < graph.V(); i++){
        //     if (!visited[i]){
        //         bfs(i);
        //     }
        // }

        // 如果只有一个component，直接调用bfs即可
        bfs(source);
    }

    ~ShortestPath(){
        delete[] visited;
        delete[] from;
        delete[] order;
    }

    // 判断顶点v和原点之间是否相连
    bool isConnected(int v){
        assert(0 < v < graph.V());
        return visited[v];
    }

    void findShortestPath(int v, vector<int> &result){
        // 利用from数组将v到source的从后到前的路径放入一个栈中，然后将栈中的元素放入result中，
        // 结果为路径的顺序
        stack<int> pathStack;
        pathStack.push(v);
        int fromSize = sizeof(from);
        vector<int> fromResult;
        for (size_t i = 0; i < fromSize; i++){
            fromResult.push_back(from[i]);
        }
        
        for (int pathVertex = from[v]; pathVertex != -1; pathVertex = from[pathVertex]){
            pathStack.push(pathVertex);
        }
        // #####错误2：栈不能按照vector的方式进行索引，只能用pop, top来提取元素#####
        while (!pathStack.empty()){
            result.push_back(pathStack.top());
            pathStack.pop();
        }
        
        return;
    }

    // 输出从原点source到顶点v的路径
    void showPath(int v){
        // 首先找到从顶点v到原点source的路径，用findShortestPath
        vector<int> path;
        findShortestPath(v, path);
        // 输出路径
        for (int i = 0; i < path.size() ; i++){
            if (i < path.size() -1){
                cout << path[i] << "-->";
            } 
            else{
                cout << path[i] << endl;
            }
        }

        return;
    }
};

#endif