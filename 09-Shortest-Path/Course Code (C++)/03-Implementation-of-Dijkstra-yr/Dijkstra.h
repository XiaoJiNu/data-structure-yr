#ifndef _03_DIJKSTRA_YR
#define _03_DIJKSTRA_YR

#include <vector>
#include <stack>
#include "IndexMinHeap.h"
#include "SparseGraph.h"

using std::vector;
using std::stack;

template <typename Graph, typename Weight>
class Dijkstra{

private:
    Graph& g;                   // 图
    int s;                      // 起始点
    Weight* distTo;             // 用于存储当前找到的s到达每个顶点的最短距离
    IndexMinHeap<Weight> ipq;   // 最小索引堆iqp，用保存目前完成了松池操作的顶点以及s到各自顶点的目前的最短距离，
                                // 用于选取最短边。这些边都没有找到最短路径
    // ### from保存的是一条边的指针，所以应该在创建vector的时候指定边的指针类型
    vector<Edge<Weight>*> from; // 每个顶点从s到它最短路径上，from保存到达这个顶点的边的指针.同时也表示顶点是否访问过
    bool *marked;               // 标记每个顶点是否找到了最短路径，如果找到了，则后面将不会再访问它

public:
    Dijkstra(Graph& graph, int startPoint): g(graph), s(startPoint), \
        ipq(IndexMinHeap<Weight>(g.V())){
        // 对各个数据进行初始化
        distTo = new Weight[g.V()];
        marked = new bool[g.V()];
        for (int i = 0; i < g.V(); i++){
            // ### 如果Weight是int，则这里执行int()，调用默认构造函数，与vector<int>()原理类似
            distTo[i] = Weight();  
            // from[i].push_back(nullptr);  // 开始每个顶点都没有最短路径的边指向它们  ###
            // from[i] = nullptr;   ###
            from.push_back(nullptr);
            marked[i] = false;
        }

        // 对起始点进行操作，入堆
        // ### 对于起始边，创建一条它到自己的边并存入from。这里可以直接用下面的语句实现吗？？？
        // from[s] = &Edge<Weight>(s, s, Weight());  
        from[s] = new Edge<Weight>(s, s, Weight());  
        distTo[s] = Weight();     // s到自身的距离为默认值0
        ipq.insert(s, Weight());  // 将s自身的边入堆  

        // 开始迭代，寻找s到每个顶点的最短路径，直到ipq为空。所有的边都会进入ipq？？？
        // ### 条件应该是ipq不为空
        while (!ipq.isEmpty()){
            // ### ----------这里提取的应该是最小元素的索引，而还是最小元素
            // int v = ipq.extractMin();  // ### 取出了ipq中最  短边所指向的顶点v
            int v = ipq.extractMinIndex(); 
            marked[v] = true;

            // 迭代顶点v的邻边，对这些邻边指向的顶点进行松池操作
            // ### 引用传递时不需要在参数前面加&
            // typename Graph::adjIterator iter(&g, v);
            typename Graph::adjIterator iter(g, v);
            for (Edge<Weight>* adjEdge = iter.begin() ; !iter.end(); adjEdge = iter.next()){
                int w = adjEdge -> getB();  // 取出这条边指向的顶点
                // 如果顶点w没有找到最短路径，则对它进行松池操作
                if (marked[w] == false){
                    // 如果顶点w没有访问过或者是访问过但是从v到达w的距离加上s到v的距离
                    // 小于当前从s到w路径的距离，可以进行松池操作
                    // ### from[w]为空表示这个顶点没有访问过
                    if (from[w] == nullptr || distTo[v] + adjEdge -> getWeight() < distTo[w]){
                        distTo[w] = distTo[v] + adjEdge -> getWeight();
                        // from[w] = adjEdge;  ### from[w]更新应该在最小堆更新之后，否则最小堆更新会报错
                        // ### ---------- 更新最小索引堆 ----------
                        // ### ipq保存的是顶点w和目前s到顶点s的最短距离，不是到w的边的权重，
                        // if (from[w] == nullptr)
                        //     ipq.insert(w, adjEdge -> getWeight());  // w没有访问过则将它插入ipq
                        // else
                        //     ipq.change(w, adjEdge -> getWeight());
                        // if (ipq.contain(w) == false)   // ipq.contain(w)也能表示顶点w是否访问过
                        //     ipq.insert(w, distTo[w]);  // w没有访问过则将它插入ipq
                        // else
                        //     ipq.change(w, distTo[w]);
                        if (from[w] == nullptr)
                            ipq.insert(w, distTo[w]);  // w没有访问过则将它插入ipq
                        else
                            ipq.change(w, distTo[w]);
                        from[w] = adjEdge;
                    }
                }
            }
        }
    }

    ~Dijkstra(){
        delete[]  distTo;
        delete[]  marked;
        delete from[s];  // ### from中只有from[s]才开辟了空间，所以只需要删除from[s]即可
    }
    // 函数1：返回从s点到w点的最短路径长度
    Weight minWeightSToW(int w){
        return distTo[w];
    }

    // 函数2：判断从s点到w点是否联通
    bool isConnectedSToW(int w){
        return marked[w];  // 如果顶点w被标记过则它和s相连
    }

    // 函数3：寻找从s到w的最短路径, 将整个路径经过的边存放在vec中
    vector<int> shortestPathSToW(int w){
        // 先从后往前将路径传入栈中
        stack<int> pathStack;
        pathStack.push(w);
        while (from[pathStack.top()] -> getA() != s){
            pathStack.push(from[pathStack.top()] -> getA());
        }
        pathStack.push(s);  // 前面没有将s放入栈中，这里放入
        // 再放入vector中
        vector<int> resultVector;
        while (!pathStack.empty()){
            resultVector.push_back(pathStack.top());
            pathStack.pop();
        }

        return resultVector;
    }

    // 函数4：打印出从s点到w点的路径 
    void showPath(int w){
        bool temp = marked[4];
        vector<int> resultVector;
        resultVector = shortestPathSToW(w);

        // 输出
        for (auto v: resultVector){
            cout << v << " ";
        }
        cout << endl;
    }
};

#endif