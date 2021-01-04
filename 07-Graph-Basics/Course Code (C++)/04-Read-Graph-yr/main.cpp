// 读入txt文件中图的参数，并利用这些参数构建图
// txt中格式： 第一行为点数与边数，剩下的行为一条边的两个顶点

#include <fstream>
#include <sstream>
#include <cstdlib>
#include "ReadGraph.h"
#include "SparseGraph.h"
#include "DenseGraph.h"

using namespace std;

int main(){
    string testG1Path = "testG1.txt";
    string testG2Path = "testG2.txt";
    
    SparseGraph g1(13, false);
    ReadGraph<SparseGraph> readG1(g1, testG1Path);
    g1.show();

    cout << endl;
    DenseGraph g2(6, false);
    ReadGraph<DenseGraph> readG2(g2, testG2Path);
    g2.show();
}
