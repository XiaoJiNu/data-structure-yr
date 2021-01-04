//
// Created by youren on 8/10/2020. DD/MM/YYYY
//

#ifndef _01_WEIGHTED_GRAPH_YR_SPARSEGRAPH_H
#define _01_WEIGHTED_GRAPH_YR_SPARSEGRAPH_H

#include <vector>
#include <iostream>
#include <iomanip>
#include "Edge.h"

using std::vector;
using std::cout;
using std::endl;


template <typename Weight>
class SparseGraph{
private:
    int vertexNum, edgeNum;              // 顶点数和边数
    bool directed;                       // 是否为有向图
    // 由于每条边用指针存储，所以这里要添加*,开始没有添加*出错
    // 邻接边. 声明一个空的vector??语法是否正确？？ 答：正确
    vector<vector<Edge<Weight>*>> adjList;  

public:
    // 创建图的时候并不需要传入边数
    SparseGraph(int n, bool directed){
        // ### 需要判断 n >= 0
        assert(n >= 0);
        vertexNum = n;
        edgeNum = 0;
        this -> directed = directed;
        // 问：为什么这里要用指针来存储每个元素？？
        // 答：为了能够表示没有边的情况，我们用一个空指针来表示，
        //     所以边在邻接表或者邻接矩阵中，统一用指针来存储每个元素
        // 错误写法1
        // adjList = vector<vector<Edge<Weight>*>>(vertexNum, new Edge<Weight>());  
        // 错误写法2
        // adjList = vector<vector<Edge<Weight>*>>(vertexNum, 
        //         vector<Edge<Weight>>(new Edge<Weight>()));  
        // 正确写法1
        // adjList = vector<vector<Edge<Weight>*>>(vertexNum, vector<Edge<Weight>*>());
        // 正确写法2，因为只需要生成长度为n的vector，每个元素默认初始化就行
        adjList = vector<vector<Edge<Weight>*>>(vertexNum);
    }

    ~SparseGraph(){
        // 由于每个元素都是由new开辟的空间，所以这里需要delete
        for (int i = 0; i < vertexNum; i++){
            for (int j = 0; j < adjList[i].size(); j++){
                delete adjList[i][j];
            }
        }
    }

    // 添加一条边
    // ### 开始添加边的时候没有传入权重void addEdge(int v, int w)
    void addEdge(int v, int w, Weight edgeWeight){
        assert(0 <= v < vertexNum);
        assert(0 <= w < vertexNum);
        // 添加v->w这条边
        adjList[v].push_back(new Edge<Weight>(v, w, edgeWeight));
        // 如果是无向图，并且v!=w则w->v也应该添加,如果v=w，前面graph[v][w]已经添加了
        // 注意：这里没有判断v,w是否已经有边的情况，因为如果要遍历graph[v]或者graph[w]
        // 才知道,时间复杂度将为平方
        if (v != w && !directed){ 
            adjList[w].push_back(new Edge<Weight>(w, v, edgeWeight));
        }
        edgeNum ++;  // 边的数量增加1
    }

    // 判断两个顶点是否有边，遍历graph[v]，如果发现它包含的边中含有顶点w则有边，否则没有
    bool hasEdge(int v, int w){   
        assert(0 <= v < vertexNum);
        assert(0 <= w < vertexNum);                                               
        for (int i = 0; i < adjList[v].size(); i++){
            // ### 这里需要用用other函数来提取吗？？可以用other，其实用getB()
            // 应该也是可以的，getB()就得到了含有顶点v这条边的另外一个顶点
            if (adjList[v][i] -> getB() == w) {                                   
                return true;
            }
        }
        return false;  
    }

    int V(){ return vertexNum;}  // 返回节点数量

    int E(){ return edgeNum;}    // 返回边的数量

    // 显示整个图的所有信息，输出第个节点的所有邻接点
    void show(){
        // cout << fixed << setprecision(2);
        for (int i = 0; i < adjList.size(); i++){
            cout << i << ": ";
            // ### 开始没有将for中的i变量变成j，导致出错
            // for (int j = 0; j < adjList[i].size(); i++){
            for (int j = 0; j < adjList[i].size(); j++){
                // ### 此处想用Edge类中的重载操作符<<输出，该怎么写？ 
                // 答：<<不应该给指针，而应该给对象
                // cout << "{" << adjList[i][j] << "} "; 
                cout << "{" << adjList[i][j] -> getB() << " w:" << adjList[i][j] -> getWeight() << "} "; 
            }
            cout << endl;
        }
    }

    // 实现邻边迭代器
    class adjIterator{
    private:
        SparseGraph& g;  // 一定要存储一个图吗？？类型一定要SparseGraph吗？？
        int vertex;
        int index;       // 用于记录邻边的序号
    public:
        adjIterator(SparseGraph& iterGraph, int v): g(iterGraph){
            vertex = v;
            index = 0;
        }
        
        Edge<Weight>* begin(){
            index = 0;
            // 当vertex有邻边时才进行迭代
            if (g[vertex].size() > 0){
                return g[vertex][index];
            }
            // nullptr和NULL的区别？？ nullptr表示空指针，NULL表示0
            return nullptr;  
        }

        Edge<Weight>* next(){
            // index在外层进行迭代的时候如果超过g[vertex].size()就终止迭代
            index ++;  
            if (index < g[vertex].size()){
                return g[vertex][index];
            }
            return nullptr;
        }

        bool end(){
            // 应该是大于邻边的数量才结束
            return index >= g[vertex].size();
        }
    };
    
};

#endif