#include "Components.h"

template <typename Graph> Components<Graph>::Components(Graph &g): graph(g){
    this->id = vecotr<int>(graph.vertexNum, -1);
    this->visited = vector<bool>(graph.vertexNum, false);
    this->ccount = 0;

    // 求连通分量
    for (size_t i = 0; i < graph.vertexNum; i++){
        if (!visited[i]){
            dfs(i);
            ccount ++;
        }
    }
}

// template <typename Graph> Components<Graph>::~Components(){}

template <typename Graph> void Components<Graph>::dfs(int i){
    visited[i] = true;
    di[i] = ccount;
    typename Graph::Iterator iter(graph, i);  // 生成迭代器 graph::正确吗??
    for (int j = iter.begin(); !iter.end(); iter.next()){
        if (!visited[j]) dfs(j);
    }
}

// 如果两个顶点的id相同，则它们是连通的
template <typename Graph> bool Components<Graph>::isConnected(int i, int j){
    if (id[i]==id[j]) 
        return true;
    else 
        return false;
}

template <typename Graph> int Components<Graph>::count(){
    return count;
}