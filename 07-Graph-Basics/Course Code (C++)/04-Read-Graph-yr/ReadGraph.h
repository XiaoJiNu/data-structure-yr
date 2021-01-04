// 读入txt文件中图的参数，并利用这些参数构建图
// txt中格式： 第一行为点数与边数，剩下的行为一条边的两个顶点
// 思路：为了方便后面复用，创建一个模板类来完成
#ifndef ReadGraph_H
#define ReadGraph_H

#include <fstream>
#include <sstream>
#include <assert.h>
#include <string>
// #include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"

using namespace std;


template <typename Graph>
class ReadGraph{
public:
    ReadGraph(Graph &graph, const string &filePath){
        ifstream graphParameter(filePath);
        assert(graphParameter.is_open());

        // 读入第一行，然后提取顶点数和边数
        string vertexEdgeNums;
        getline(graphParameter, vertexEdgeNums);
        int vertexNum, edgeNum;
        istringstream temp(vertexEdgeNums);
        temp >> vertexNum >> edgeNum;
        assert(graph.V()==vertexNum);  // 判断给定顶点数与图的顶点数是否相等

        // 添加边数
        string line;
        while (getline(graphParameter, line)) {
            istringstream ss(line);
            int a, b;
            ss >> a >> b;
            graph.addEdge(a, b);
        }
    }
    ~ReadGraph(){}
};


#endif