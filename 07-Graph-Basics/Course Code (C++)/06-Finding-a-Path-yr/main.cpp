#include <iostream>
#include <sstream>
#include "Components-yr.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Path.h"

using namespace std;


int main(){
    // 创建一个稀疏图并显示它
    bool directed = false;
    string G1Path = "testG.txt";
    SparseGraph sg(7, directed);
    ReadGraph<SparseGraph> readG1(sg, G1Path);
    sg.show();
    cout << endl;

    Path<SparseGraph> findOnePath(sg, 0);
    findOnePath.showPath(6);
    return 0;
}