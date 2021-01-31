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
    for(;(root << 1) + 1 <= length; ){
        int lchild = (root << 1) + 1;
        int rchild = (root << 1) + 2;
        int large = root;
        if(lchild <= length && arr[lchild] > arr[large])    large = lchild;
        if(rchild <= length && arr[rchild] > arr[large])    large = rchild;
        if(root != large){
            swap(arr[root], arr[large]);
            root = large;
        }else
            break;
    }
}


void MaxheapBuild(vector<int> &arr, int length){
    for(int i = length / 2; i >= 0; -- i){
        heapBuild(arr, i, length);
    }
}


void heapSort(vector<int> &arr, int length){
    MaxheapBuild(arr, length);
    for(int j = length; j >= 0; -- j){
        swap(arr[0], arr[j]);
        length --;
        heapBuild(arr, 0, length);
    }
    return;
}

int main(){
    vector<int> arr{5,2,3,1};
    heapSort(arr, arr.size() - 1);
    for(int n : arr)
        cout << n << endl;
    return 0;
}
