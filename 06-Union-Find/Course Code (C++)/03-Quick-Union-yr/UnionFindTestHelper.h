#ifndef _02_QIUCK_FIND_YR_UNIONFINDTESTHELPER_H
#define _02_QIUCK_FIND_YR_UNIONFINDTESTHELPER_H

#include <iostream>
#include <ctime>
#include "UnionFind1.h"
#include "UnionFind2.h"

// using namespace std;

namespace  UnionFindTestHelper{
    
    // 输入元素的数量n
    void ufTest1(int n){
        srand(time(NULL));              // 生成随机种子
        time_t startTiime = clock();    // 计时

        // 生成并查集
        UF1::UnionFind uf = UF1::UnionFind(n);
        // 随机选择两个元素进行合并
        for (int i = 0; i < n; i++){
            int p = rand() % n;
            int q = rand() % n;
            // TO DO ..
            uf.unionElements(p, q);
        }
        // 随机选择两个元素，查看是否连接
        for (int i = 0; i < n; i++){
            int a = rand() % n;
            int b = rand() % n;
            uf.isConnected(a, b);
        }
        
        time_t endTime = clock();

        std::cout << "process time is: " << \
                  double(endTime - startTiime) / CLOCKS_PER_SEC << std::endl;
    }

    // 测试第二版本的并查集, 测试元素个数为n, 测试逻辑和之前是完全一样的
    // 思考一下: 这样的冗余代码如何消除?
    // 由于这个课程不是设计模式课程, 在这里就不过多引入相关的问题讲解了。留作给大家的思考题:)
    void testUF2( int n ){

        srand( time(NULL) );
        UF2::UnionFind uf = UF2::UnionFind(n);

        time_t startTime = clock();

        for( int i = 0 ; i < n ; i ++ ){
            int a = rand()%n;
            int b = rand()%n;
            uf.unionElements(a,b);
        }
        for(int i = 0 ; i < n ; i ++ ){
            int a = rand()%n;
            int b = rand()%n;
            uf.isConnected(a,b);
        }
        time_t endTime = clock();

        std::cout<<"UF2, "<<2*n<<" ops, "<<
                    double(endTime-startTime)/CLOCKS_PER_SEC<<" s"<< std::endl;
    }

}

#endif