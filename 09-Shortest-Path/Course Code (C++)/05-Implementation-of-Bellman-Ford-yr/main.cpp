#include <iostream>
#include <vector>
#include <iomanip>

#include "Edge.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Dijkstra.h"
#include "BellmanFord.h"

using namespace std;
using weight = int;

int main(){
    // string filePath = "testG_negative_circle.txt";
    string filePath = "testG2.txt";

    
    // 创建一个稀疏图并读入它的参数
    // ### Bellman不能用于有负权边的无向图，注意这里是有向图
    SparseGraph<weight> g = SparseGraph<weight>(5, true);
    ReadGraph<SparseGraph<weight>, weight> readGraph(g, filePath);
    g.show();
    cout << endl;

    // 用Bellman-Ford求出顶点s到每个顶点的最短距离
    int s = 0;
    BellmanFord<SparseGraph<weight>, weight> BellmanPath(g, s);
    for (int w = 0; w < g.V(); w++) {
        // 如果顶点w与顶点0相连，输出0到它的最短路径
        if(BellmanPath.isConnectedSToW(w) == true){
            cout << s << "-> " << w << ": ";
            BellmanPath.showPath(w);
        }
        else
            cout << "no path to " << w << endl;
    }

    return 0;
}
