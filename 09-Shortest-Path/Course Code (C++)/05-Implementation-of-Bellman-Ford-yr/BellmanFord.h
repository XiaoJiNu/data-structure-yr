// 
// Created by yr on 9/4/2020
// 
#ifndef _05_IMPLEMENTATION_OF_BELLMAN_FORD_YR_BELLMANFORD_H
#define _05_IMPLEMENTATION_OF_BELLMAN_FORD_YR_BELLMANFORD_H

#include <iostream>
#include <vector>

#include "SparseGraph.h"
#include "DenseGraph.h"
#include "Edge.h"

template <typename Graph, typename Weight>
class BellmanFord{
private:
    Graph& g;
    int s;
    Weight *distTo;
    vector<Edge<Weight>*> from;
    bool hasNegativeCycle;

public:
    BellmanFord(Graph& graph, int sourceNode): g(graph){
        // 初始化各个变量
        s = sourceNode;
        distTo = new Weight[g.V()];
        for (int i = 0; i < g.V(); i++){
            distTo[i] = Weight();   // ### 这里直接将distTo每个元素初始化为0可以吗
            from.push_back(nullptr);
        }
        hasNegativeCycle = false;

        // ### 对起始点s进行初始化，让指向它的最短路径为它自己。
        from[s] = new Edge<Weight>(s, s, Weight());

        // ----------运行BellmanFord算法----------
        // 循环图的顶点数V-1次
        for (int i = 0; i < g.V(); i++){
            // 每次循环迭代所有的边，如果满足条件就进行松池操作
            typename Graph::adjIterator iter(g, i);
            for (Edge<Weight>* adjEdge = iter.begin(); !iter.end(); adjEdge = iter.next()){
                int v = adjEdge -> getA();  // 边的起点
                int w = adjEdge -> getB();  // 边的终点
                if (from[v] != nullptr && from[w] == nullptr || \
                    distTo[w] > distTo[v] + adjEdge -> getWeight()){
                    from[w] = adjEdge;
                    distTo[w] = distTo[v] + adjEdge -> getWeight();
                }
            }
        }

        // 再循环一次，判断是否存在负权环
        hasNegativeCycle = checkNegativeCycle();
    }

    ~BellmanFord(){
        delete[] distTo;
        delete from[s];
    }

    // 循环完V-1次后，再循环一次，遍历所有顶点的邻边，如果此时图中还有可以松池的点，证明有负权环
    bool checkNegativeCycle(){
        for (int i = 0; i < g.V(); i++){
            typename Graph::adjIterator iter(g, i);
            for (Edge<Weight>* adjEdge = iter.begin(); !iter.end(); adjEdge = iter.next()){
                int v = adjEdge -> getA();
                int w = adjEdge -> getB();
                // ### 这里还需要判断顶点v是否能到达吗？？
                if (distTo[w] > distTo[v] + adjEdge -> getWeight()){
                    return true;
                }
            }
        }
        // 遍历完所有的边后都没有发现负权环，返回false
        return false;
    }

    // 函数1：返回从s点到w点的最短路径长度
    Weight minWeightSToW(int w){
        return distTo[w];
    }

    // 函数2：判断从s点到w点是否连通
    bool isConnectedSToW(int w){
        if (from[w] != nullptr)  // 如果顶点w可以到达，则证明和s连通
            return true;
    }

    // 函数3：寻找从s到w的最短路径, 将整个路径经过的边存放在vec中
    vector<int> shortestPathSToW(int w){
        // 先从后往前将路径传入栈中
        stack<int> pathStack;
        pathStack.push(w);
        while (from[pathStack.top()] -> getA() != s){
            pathStack.push(from[pathStack.top()] -> getA());
        }
        pathStack.push(s);  // 前面没有将s放入栈中，这里放入
        // 再放入vector中
        vector<int> resultVector;
        while (!pathStack.empty()){
            resultVector.push_back(pathStack.top());
            pathStack.pop();
        }

        return resultVector;
    }

    // 函数4：打印出从s点到w点的路径 
    void showPath(int w){
        vector<int> resultVector;
        resultVector = shortestPathSToW(w);

        // 输出
        for (auto v: resultVector){
            cout << v << " ";
        }
        // 输出s到w路径的权重和
        cout << "weight: "<< minWeightSToW(w);
        cout << endl;
    }
};

#endif