kruskal算法

思路：首先用最小堆对各个边对排序，然后依次取出各个最小边，只要没有形成环状，证明这条边就是一条最小生成树的边。因为最小生成树不能形成环，同时一条边如果是没有添加到最小生成树的边中最小的边，那么一定可以找到一个切分使这个边是横切边，根据切分定理它一定属于最小生成树的边。只要取出V-1条边就得到了最小生成树。