/************************************************************************
    > File Name: heap_sort.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 日  1/31 12:39:54 2021
************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
using namespace std;

// 堆排序

void heapBuild(vector<int> &arr, int root, int length){
    int lchild = root * 2 + 1;
    if(lchild < length){
        int flag = lchild;
        int rchild = lchild + 1;
        if(rchild < length){
            if(arr[lchild] < arr[rchild])
                flag = rchild;
        }
        if(arr[root] < arr[flag]){
            swap(arr[root], arr[flag]);
            heapBuild(arr, flag, length);
        }
    }
    return;
}

void heapSort(vector<int> &arr, int length){
    for(int i = length / 2; i >= 0; -- i){
        heapBuild(arr, i, length); 
    }
    for(int j = length - 1; j > 0; -- j){
        swap(arr[0], arr[j]);
        heapBuild(arr, 0, j);
    }
    return;
}

int main(){
    vector<int> arr{1,3,2,5,4,7,6,8,9};
    heapSort(arr, arr.size() - 1);
    for(int n : arr)
        cout << n << endl;
    return 0;
}
