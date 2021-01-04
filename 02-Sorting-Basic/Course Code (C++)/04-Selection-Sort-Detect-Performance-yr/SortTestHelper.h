#ifndef _04_SELECTION_SORT_H
#define _04_SELECTION_SORT_H

#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;


namespace SortTestHelper{
    template <typename T>
    T* generateRandomArray(int n, T bottoum, T upper){
        T *arr = new int[n];
        srand(time(NULL));  // 每次使用随机数时，需要设定随机种子
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (upper - bottoum + 1);
        
        return arr;
    }

    
    template <typename T>
    bool isSorted(T arr[], int n){
        for (int i = 0; i < n; i++){
            if (arr[i] > arr[i+1])
                return false;
        }

        return true;
    }


    template <typename T>
    void showArray(T arr[], int n){
        for (int i = 0; i < n; i++){
            cout << arr[i] << " ";
        }
        
        return;
    }

    template <typename T>
    void testSort(const string sortName, void (*sort)(T arr[], int n), T a[], int n){
        clock_t startTime = clock();
        sort(a, n);
        clock_t endTime = clock();

        showArray(a, n);
        cout << sortName << " time cost is " <<
             double(endTime - startTime) / CLOCKS_PER_SEC << "s ";
        
    }
}

#endif