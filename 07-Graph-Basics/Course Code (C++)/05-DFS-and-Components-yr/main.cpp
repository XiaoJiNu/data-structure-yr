#include <iostream>
#include <sstream>
#include "Components-yr.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"

using namespace std;


int main(){
    // 创建一个稀疏图并计算它的component数量
    bool directed = false;
    string G1Path = "testG1.txt";
    SparseGraph sg(13, directed);
    ReadGraph<SparseGraph> readG1(sg, G1Path);
    Component<SparseGraph> components(sg);
    int componentsNum = components.count();
    cout << "component number of sg is " << componentsNum << endl;
    return 0;
}