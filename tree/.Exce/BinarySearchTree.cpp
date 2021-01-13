/************************************************************************
    > File Name: BinarySearchTree.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 三  1/13 13:19:16 2021
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

#define VAL(n)  (n ? n->val : 0)
#define SIZE(n) (n ? n->size : 0)
#define L(n)    (n ? n->lchild : nullptr)
#define R(n)    (n ? n->rchild : nullptr)


typedef struct Node{
    int val, size;
    Node *lchild, *rchild;
}Node;

void update_size(Node *root){
    root->size = SIZE(L(root)) + SIZE(R(root)) + 1;
    return;
}

Node * getNewNode(int target){
    Node * p = (Node *)malloc(sizeof(Node));
    p->val = target;
    p->size = 1;
    p->lchild = p->rchild = nullptr;
    return p;
}

int search(Node *root, int target){
    //寻找 target 是否存在root这棵树中
    if(root == nullptr)
        return 0;
    if(root->val == target)
        return 1;
    if(root->val > target)
        return search(root->lchild, target);
    else
        return search(root->rchild, target);
}

int search_k(Node *root, int k){
    //寻找 root这棵树中第k大的数
    if(root == nullptr || root->size < k)
        return -1;
    if(SIZE(L(root)) == k - 1)
        return root->val;
    if(k <= SIZE(L(root)))
        return search_k(root->lchild, k);
    else
        return search_k(root->rchild, k - SIZE(L(root)) - 1);
}

Node * insert(Node *root, int target){
    if(root == nullptr)
        return getNewNode(target);
    if(root->val == target)
        return root;
    if(root->val > target)
        root->lchild = insert(root->lchild, target);
    else
        root->rchild = insert(root->rchild, target);
    update_size(root);
    return root;
}
    
Node * predecessor(Node *root){
    Node * temp = root->lchild;
    while(temp->rchild != nullptr)
        temp = temp->rchild;
    return temp;
}

Node * erase(Node *root, int target){
    if(root == nullptr) return nullptr;
    if(root->val > target)
        root->lchild = erase(root->lchild, target);
    else if(root->val < target)
        root->rchild = erase(root->rchild, target);
    else{
        if(root->lchild == nullptr || root->rchild == nullptr){
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->val = temp->val;
            root->lchild = erase(root->lchild, root->val);
        }
    }
    update_size(root);
    return root;
}

void print(Node *root){
    if(root == nullptr) return;
    printf("(%d[%d], %d, %d)\n",
            VAL(root),SIZE(root),
            VAL(L(root)),
            VAL(R(root))
            );
    return;
}

void output(Node *root){
    if(root == nullptr) return;
    output(root->lchild);
    print(root);
    output(root->rchild);
    return;
}

void output_k(Node *root, int k){
    //输出root这棵树前k个数
    if(root == nullptr) return;
    if(SIZE(L(root)) >= k)
        output_k(root->lchild, k);
    else{
        output(root->lchild);
        print(root);
        output_k(root->rchild, k - SIZE(L(root)) - 1);
    }
    return;
}



int main(){
    int op, val;
    Node *root = nullptr;
    while(~scanf("%d%d",&op, &val)){
        switch(op){
            case 0: {
                        printf("search %d, result : %d\n", val, search(root, val)); 
                        break;
                    }
            case 1: {
                        printf("insert %d\n", val);
                        root = insert(root, val);
                        break;
                    }
            case 2: {
                        printf("erase %d\n", val);
                        root = erase(root, val);
                        break;
                    }
            case 3: {
                        printf("search %dth, val : %d\n", val, search_k(root, val));
                        break;
                    }
            case 4: {
                        printf("output pre-%d element\n", val);
                        output_k(root, val);
                        printf("---------------\n");
                        break;
                    }
        }
        if(op == 1 || op == 2){
            output(root);
            printf("---------------\n");
        }
    }

    return 0;
}
