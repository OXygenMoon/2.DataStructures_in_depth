/************************************************************************
    > File Name: trie.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 一  3/ 8 21:44:15 2021
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

typedef struct TrieTree{
    char data;
    TrieTree* children[26];
    bool isEndingChar;
    TrieTree(char ch = '/') : data(ch){ isEndingChar = false; for(auto& c : children) c = nullptr; }
}TT;

TT* root = new TT();



void insert(string text){
    TT* p = root;
    for(int i = 0; i < text.length(); ++ i){
        int index = text[i] - 'a';
        if(p->children[index] == nullptr){
            TT* node = new TT(text[i]);
            p->children[index] = node; 
        }
        p = p->children[index];
    } 
    p->isEndingChar = true;
}

bool find(string pattern){
    TT* p = root;
    for(int i = 0; i < pattern.length(); ++ i){
        int index = pattern[i] - 'a';
        if(p->children[index] == nullptr)   return false;
        p = p->children[index];
    }
    if(p->isEndingChar == false)    return false;
    return true;
}


int main(){
    insert("hello");
    cout << find("hello");
    cout << find("he");
    return 0;
}
