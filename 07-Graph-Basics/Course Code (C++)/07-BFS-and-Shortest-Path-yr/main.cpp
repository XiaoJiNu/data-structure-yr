#include <iostream>
#include <sstream>


#include "Components-yr.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Path.h"
#include "ShortestPath.h"

using namespace std;


int main(){
    // 读入txt文档，创建图
    string filename = "testG.txt";
    SparseGraph graph1(7, false);
    ReadGraph<SparseGraph> readGraph1(graph1, filename);
    // 通过广度优先遍历得到最短路径
    // 创建模板类必须要提供模板类型
    ShortestPath<SparseGraph> shortesPath(graph1, 0);
    shortesPath.showPath(3);

}


























// int main(){
//     // 创建一个稀疏图并显示它
//     bool directed = false;
//     string G1Path = "testG.txt";
//     SparseGraph sg(7, directed);
//     ReadGraph<SparseGraph> readG1(sg, G1Path);
//     sg.show();
//     cout << endl;

//     Path<SparseGraph> findOnePath(sg, 0);
//     findOnePath.showPath(6);
//     return 0;
// }