/************************************************************************
    > File Name: quick_sort.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 五  1/15 13:52:30 2021
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

void quickSort(vector<int> &arr, int left, int right){
    if(left >= right)
        return;
    int i,j,base;
    i = left, j = right;
    base = arr[left];
    while(i < j){
        while(arr[j] >= base && i < j)
            j--;
        while(arr[i] <= base && i < j)
            i++;
        if(i < j){
            swap(arr[i], arr[j]);
        }
    }
    //基准数归位
    arr[left] = arr[i];
    arr[i] = base;
    quickSort(arr, left, i - 1);
    quickSort(arr, i + 1, right);
    return;
}




int main(){
    vector<int> arr{1,3,2,7,6,5,4,9,8};
    quickSort(arr, 0, arr.size() - 1);
    for(int n : arr)
        cout << n << endl;    
    return 0;
}   
