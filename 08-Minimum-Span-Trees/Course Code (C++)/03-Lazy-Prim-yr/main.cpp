#include <iostream>
#include <vector>
#include <iomanip>

#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "LazyPrim.h"
#include "Edge.h"

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

    LazyPrim<SparseGraph<weight>, weight> lazyprim(g);
    vector<Edge<weight>> minGenTree = lazyprim.mstEdges();
    cout << "minimum gernerate tree is: " << endl;
    for ( auto edge : minGenTree)
        cout << edge << endl;
    cout << "minimum value is: " << lazyprim.result() << endl;

    return 0;
}


// int main(){
//     // 在main()函数里面设置了精度，由main函数调用的函数的输出依然保持这个输出精度
//     cout << fixed << setprecision(2);
//     string filePath = "testG1.txt";
    
//     // 创建一个稀疏图并读入它的参数
//     // SparseGraph<weight> g(8，false);  // ###为什么这种方式创建对象不行？？
//     SparseGraph<weight> g = SparseGraph<weight>(8, false);
//     // ReadGraph<SparseGraph, weight> readGraph(g, filePath);  //此种写法错误
//     ReadGraph<SparseGraph<weight>, weight> readGraph(g, filePath);
//     g.show();
//     cout << endl;
    
//     // 创建稠密图
//     DenseGraph<weight> dg(8, false);    
//     ReadGraph<DenseGraph<weight>, weight>(dg, filePath);
//     dg.show();

//     return 0;
// }