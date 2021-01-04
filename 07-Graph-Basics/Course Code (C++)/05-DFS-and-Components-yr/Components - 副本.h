#ifndef Components_H
#define Components_H

#include<vector>
using std::vector;

template <typename Graph>
class Components{
private:
    int ccount;
    vector<int> id;
    vector<bool> visited;
    Graph &graph;
    
public:
    // Components(Graph &g): graph(g); 初始化参数列表应该在实现函数的时候写出来
    Components(Graph &g);
    // ~Components(); 
    void dfs(int i);
    bool isConnected(int i, int j);
    int count();
};

#endif