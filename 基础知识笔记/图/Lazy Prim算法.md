###Lazy Prim算法思路

~~~c++
template <typename Graph, typename Weight>
class LazyPrim{
private:
	图g;
    最小堆(用于存放横切边)pq;
    用于存放最小路径的所有边的向量minEdge;
    最小路径的权值和minWeight;
    用于标记每个顶点是否被访问的向量mark,用指针实现;
    访问一个没有被访问过的顶点的函数visit,它会将与这个顶点相连的横切边全部放入最小堆中，用于后面寻找最小堆中的权值最小的边；
public:
    // 构造函数，在构造函数中完成lazy prim算法
	LazyPrin(Graph& graph): g(graph){
        访问顶点0，它会将顶点0的横切边放入最小堆中；
        /*
         这里是将图中所有的边都放入最小堆中，每次取出权值最小的横切边放入最小路径中，直到取出了所有的边结束。注意这里是取出权值		 最小的横切边，如果不是横切边则跳过进行下一次循环，这条边被丢弃。
         与广度优先搜索的区别：
         	广度优先搜索：先将根结点放入队列中，然后依次将它的相邻节点放入队列，并弹出这个节点，直到所有节点都放入队列并且全部弹			  出，队列为空时结束广度优先搜索算法。它是对节点进行操作，以队列为辅助数据结构
         	Lazy Prim: 先将根节点的所有边放入最小堆中，然后取出最小横切边，将最小横切边中未访问过的顶点的横切 
        */
        当最小堆中的元素不为空时：
            找到最小堆中的权值最小的边；
            // 此时在最小堆中已经将这条不满足条件的边取出了
            如果这个边两个顶点都被访问过，跳过这次循环，继续寻找最小堆中下一个最小的边；
            否则将最小边放入minEdge;
        	访问这个最小边中没有访问过的那个顶点，将它的所有横切边放入最小堆，在下一次循环中，又会找到权值最小的边进行操作；
    }
};



~~~



bug1：开始在Edge.h类中对每条边的大小比较操作符重载写反了

bug2:  没有调用minGenTree.clear();，并且保存最小生成树的权值和的变量没有初始化，导致每次运行的最小结果不一致