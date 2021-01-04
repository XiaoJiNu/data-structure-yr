#ifndef _02_QIUCK_FIND_YR_UNIONFINDTESTHELPER_H
#define _02_QIUCK_FIND_YR_UNIONFINDTESTHELPER_H

#include <iostream>
#include <ctime>
#include "UnionFind1.h"

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

}

#endif