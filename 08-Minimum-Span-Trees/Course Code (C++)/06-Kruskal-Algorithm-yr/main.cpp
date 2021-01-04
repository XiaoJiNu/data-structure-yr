#include <iostream>
#include <vector>
#include <iomanip>

#include "Edge.h"
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "LazyPrim.h"
#include "OptimPrim.h"
#include "Kruskal.h"

using namespace std;
using weight = float;

int main(){
    // 在main()函数里面设置了精度，由main函数调用的函数的输出依然保持这个输出精度
    cout << fixed << setprecision(2);
    string filePath = "testG1.txt";
    
    // 创建一个稀疏图并读入它的参数
    // SparseGraph<weight> g(8，false);  // ###为什么这种方式创建对象不行？？
    SparseGraph<weight> g = SparseGraph<weight>(8, false);
    ReadGraph<SparseGraph<weight>, weight> readGraph(g, filePath);
    g.show();
    cout << endl;

    // lazy prim
    LazyPrim<SparseGraph<weight>, weight> lazyprim(g);
    vector<Edge<weight>> minGenTree = lazyprim.minGenTreeEdges();
    cout << "minimum gernerate tree is: " << endl;
    for ( auto edge : minGenTree)
        cout << edge << endl;
    cout << "minimum value is: " << lazyprim.minGenTreeValue() << endl;

    // optimal prim
    OptimPrim<SparseGraph<weight>,weight> optimprim(g);
    vector<Edge<weight>> optimMinGenTree = optimprim.minGenTreeEdges();
    cout << "optimal minimum gernerate tree is: " << endl;
    for ( auto edge : optimMinGenTree)
        cout << edge << endl;
    cout << "minimum value is: " << optimprim.minGenTreeValue() << endl;

    // Kruskal
    Kruskal<SparseGraph<weight>, weight> kruskalAlgrithm(g);
    vector<Edge<weight>> kruskalMinGenTree = kruskalAlgrithm.minGenTreeEdges();
    for (auto edge: kruskalMinGenTree){
        cout << edge << endl;
    }
    cout << "minimum value is: " << optimprim.minGenTreeValue() << endl;

    return 0;
}

