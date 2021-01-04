#ifndef Component_H
#define Component_H

#include <vector>
using std::vector;

template <typename Graph>
class Component{
private:
    int ccount;
    // vector<int> id;
    // vector<bool> visited;
    bool *visited;
    int *id;
    Graph &graph;
    
public:
    // Component(Graph &g): graph(g); 初始化参数列表应该在实现函数的时候写出来
    Component(Graph &g): graph(g){
        // vertexNum是graph的私有变量，不能直接调用，所以通过函数来引用它的值，防止它
        // 被改变
        // this->id = vector<int>(graph.vertexNum, -1);
        // this->visited = vector<bool>(graph.vertexNum, false);  
        // this->id = vector<int>(graph.V(), -1);
        // this->visited = vector<bool>(graph.V(), false);
        id = new int[graph.V()];
        visited = new bool[graph.V()];
        for (int i = 0; i < graph.V(); i++){
            id[i] = -1;
            visited[i] = false;
        }
        this->ccount = 0;

        // 求连通分量
        for (int i = 0; i < graph.V(); i++){
            if (!visited[i]){
                dfs(i);
                ccount ++;
            }
        }
    }

    ~Component(){
        delete[] id;
        delete[] visited;
    }

    void dfs(int i){
        visited[i] = true;
        id[i] = ccount;
        typename Graph::adjIterator iter(graph, i);  // 生成迭代器 graph::正确吗??
        // **********开始写成了下面这句，没有j=iter.next()，结果不正确
        // for (int j = iter.begin(); !iter.end(); j = iter.next()){
        for (int j = iter.begin(); !iter.end(); j = iter.next()){
            if (!visited[j]) dfs(j);
        }
    }

    bool isConnected(int i, int j){
        if (id[i]==id[j]) 
            return true;
        else 
            return false;
    }

    int count(){
        return ccount;
    }
};

#endif