#include <iostream>
#include "MaxHeap.h"

using namespace std;
using Item = int;

int main(){
    // 创建一个大顶堆
    int capacity = 100;
    MaxHeap<Item> pq(capacity);

    cout << "size of MaxHeap is "<< pq.size() << endl;
}
    
