#ifndef FIND_A_PATH_PATH_H
#define FIND_A_PATH_PATH_H

#include<vector>
#include<iostream>
#include<stack>

using std::vector;
using std::cout;
using std::endl;
using std::stack;

template <typename Graph>
class Path{
private:
    bool *visited;
    int *from;
    Graph &graph;
    int s;  // 原点序号

    // 深度优先遍历
    void dfs(int i){
        visited[i] = true;
        // 错误1：开始没有创建adjIter迭代对象，直接用graph.begin()，出错
        typename Graph::adjIterator adjIter(graph, i);
        for (int v = adjIter.begin(); !adjIter.end(); v=adjIter.next()){
            // 错误2：segmentaion fault错误，因为没有对访问过的点进行判断，
            // 当图中有环时会一直访问下去，导致死循环出现内存消尽的情况(个人分析)
            if (visited[v] == false){
                from[v] = i;
                dfs(v);
            }
        }
    }

public:
    Path(Graph &g, int source): graph(g) {
        // 对各个成员变量赋值
        visited = new bool[graph.V()];
        from = new int[graph.V()];
        for (int i = 0; i < graph.V(); i++){
            visited[i] = false;
            from[i] = -1;
        }
        s = source;

        // 利用深度优先遍历将与s相连的顶点全部访问，同时得到各个顶点在
        // 深度优先遍历过程的的前一个顶点序号，保存在数组from中
        dfs(s);
    }

    ~Path(){
        delete[] visited;
        delete[] from;
    }

    void findS2WPath(int w, vector<int> &pathVector){
        // 先将路径顶点从from数组中提取出来放入栈中，再从栈中提出来放入vector
        stack<int> tempStack;
        // 错误3：开始直接令p为w的前一个顶点序号，最终的路径中将不会包含w
        // int p = from[w];
        int p = w;
        while (p!=-1){
            tempStack.push(p);
            p = from[p];
        }
        while (!tempStack.empty()){
            pathVector.push_back(tempStack.top());
            tempStack.pop();
        }
    }

    void showPath(int w){
        vector<int> pathVector;
        findS2WPath(w, pathVector);

        // 输出路径
        for (int i = 0; i < pathVector.size(); i++){
            cout << pathVector[i];
            if (i < pathVector.size() -1 ){
                cout << "-->";
            } else 
                cout << endl; 
        }
    }
};


#endif