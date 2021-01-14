/************************************************************************
    > File Name: merge_sort.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 四  1/14 20:38:22 2021
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

void merge(vector<int> &arr, int left, int mid, int right){
    vector<int> L(mid - left + 1);
    vector<int> R(right - mid);
    int i,j,k;
    for(i = 0; i < L.size(); ++ i){
        L[i] = arr[left + i];
    }
    for(j = 0; j < R.size(); ++ j){
        R[j] = arr[mid + 1 + j];
    }
    i = 0;
    j = 0;
    k = left;
    while(i < L.size() && j < R.size()){
        if(L[i] >= R[j]){
            arr[k] = R[j];
            j++;
        } else {
            arr[k] = L[i];
            i++;
        }
        k++;
    } 
    while(i < L.size()){
        arr[k] = L[i];
        k++;
        i++;
    }
    while(j < R.size()){
        arr[k] = R[j];
        k++;
        j++;
    }
}

void mergeSort(vector<int> &arr, int left, int right){
    if(left < right){
        int mid = left + ((right - left) >> 1);
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
    return;
}


int main(){
    vector<int> arr{1,3,2,4,5,6,9,7,8};
    mergeSort(arr,0, arr.size() - 1);    
    for(auto n : arr){
        cout << n << endl;
    }
    return 0;
}
