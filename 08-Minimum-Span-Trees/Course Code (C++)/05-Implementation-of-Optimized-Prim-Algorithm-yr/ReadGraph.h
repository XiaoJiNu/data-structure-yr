#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include "SparseGraph.h"
using namespace std;

template <typename Graph, typename Weight>
class ReadGraph{
public:
    // 模板类的类型不一定要在构造函数中传入，在定义模板时<>中也可以传入
    ReadGraph(Graph& graph, string& filePath){
        // 读入第一行
        ifstream graphFile(filePath);
        int vertexNum, edgeNum;
        string line;
        // graphFile.getline(line);  // ### 此句错误
        getline(graphFile, line);
        istringstream sstreamLine(line);
        sstreamLine >> vertexNum >> edgeNum;
        assert(vertexNum == graph.V());  // 判断输入数据与图顶点是否相同

        // 读取剩下的边
        int v, w;  // 定义两个顶点
        Weight weight;     
        // while (getline(graphFile, line)){  用边数控制读入的行数
        for (int i= 0; i < edgeNum; i++){ 
            getline(graphFile, line);
            istringstream sstreamLine(line);
            sstreamLine >> v >> w >> weight;  // 提取顶点及权重参数
            assert(0 <= v < vertexNum);
            assert(0 <= w < vertexNum);
            graph.addEdge(v, w, weight);
        }
    }
};