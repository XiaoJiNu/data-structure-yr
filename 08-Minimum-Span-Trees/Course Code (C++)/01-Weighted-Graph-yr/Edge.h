// ifndef后面的标识符不能以数字开头，可以是字母或者下划线开头
#ifndef _01_WEIGHTED_GRAPH_YR_EDGE_H
#define _01_WEIGHTED_GRAPH_YR_EDGE_H

#include <cassert>
#include <iostream>

using std::ostream;

template <typename Weight>
class Edge{
private:
    // 注：其实每一条边都可以看作是有向边，就算是无向边，在存储的时候也可以
    // 看作有向边来存储，因为在邻接矩阵和邻接表中，无向边也会存储两为两个元素
    int a, b;         // 顶点，如果是有向边，由a指向b
    Weight weight;    // 权值

public:
    Edge(int a, int b, Weight w){
        this -> a = a;
        this -> b = b;
        weight = w;
    }

    Edge(){}

    ~Edge(){}

    // 获取顶点以及权值
    int getA(){ return a;}
    int getB(){ return b;}
    // ### 这里开始写成了返回值为int型，应该返回Weight型
    Weight getWeight(){ return weight;}


    // 给定这条边的顶点v时，返回另一个顶点w
    int other(int v){ return (v==a) ? b : a;}

    // 定义一个输出运算符重载符，给定一条边和输入流，输出边的信息
    // 这里的e为何可以直接访问边a, b ？？ 为什么这里不用模板来定义e？？e代表的是什么？？
    // ### 使用ostream需要声明在std中，using std::ostream
    friend ostream& operator<<(ostream& os, const Edge& e){
        os << e.a << "->" << e.b << ":" << e.weight;
        return os;
    }

    // 给定一条边，比较这条边和当前这条边的大小，给定边是Edge的实例
    bool operator>(Edge<Weight>& e){
        return weight > e.getWeight();
    }

    bool operator>=(Edge<Weight>& e){
        return weight >= e.getWeight();
    }

    bool operator<(Edge<Weight>& e){
        return weight < e.getWeight();
    }

    bool operator<=(Edge<Weight>& e){
        return weight <= e.getWeight();
    }

    bool operator==(Edge<Weight>& e){
        return weight == e.getWeight();
    }
};

#endif
