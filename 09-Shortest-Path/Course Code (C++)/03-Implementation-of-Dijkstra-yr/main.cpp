#include <iostream>
#include <vector>
#include <iomanip>

#include "Edge.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Dijkstra.h"

using namespace std;
using weight = int;

int main(){
    string filePath = "testG1.txt";
    
    // 创建一个稀疏图并读入它的参数
    // SparseGraph<weight> g(8，false);  // ###为什么这种方式创建对象不行？？
    SparseGraph<weight> g = SparseGraph<weight>(5, false);
    ReadGraph<SparseGraph<weight>, weight> readGraph(g, filePath);
    g.show();
    cout << endl;

    // 用dijkstra求出0到每个顶点的最短距离
    Dijkstra<SparseGraph<weight>, weight> djkPath(g, 0);
    for (int w = 0; w < g.V(); w++) {
        // 如果顶点w与顶点0相连，输出0到它的最短路径
        if(djkPath.isConnectedSToW(w) == true){
            cout << "0 -> " << w << ": ";
            djkPath.showPath(w);
        }
        else
            cout << "no path to " << w << endl;
    }

    return 0;
}
