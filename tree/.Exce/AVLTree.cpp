/************************************************************************
    > File Name: AVLTree.cpp
    > Author: Lao Zhenyu
    > Mail: LaoZhenyu_961112@163.com 
    > Created Time: 三  1/13 14:05:59 2021
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

#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define H(n) (n->h)

typedef struct Node{
    int val, h;
    Node *lchild, *rchild;
}Node;

//虚拟空节点
Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
    void init_NIL(){
        NIL->val = 0, NIL->h = 0;
        NIL->lchild = NIL->rchild = nullptr;
    }

Node *getNewNode(int target){
    Node *p = (Node *)malloc(sizeof(Node));
    p->val = target;
    p->h = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

void clear(Node *root){
    if(root == NIL)
        return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

void update_height(Node *root){
    root->h = (H(L(root))) > (H(R(root))) ? (H(L(root)) + 1) : (H(R(root)) + 1);
    return;
}

Node * right_rotate(Node *root){
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    update_height(root);
    update_height(temp);
    return temp;
}


Node * left_rotate(Node *root){
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    update_height(root);
    update_height(temp);
    return temp;
}

//调整
Node *maintain(Node * root){
    //平衡调整
    if(abs(H(L(root)) - H(R(root))) <= 1)   return root;
    if(root->lchild->h > root->rchild->h){
        //LR先小左旋
        if(root->lchild->lchild->h < root->lchild->rchild->h)
            root->lchild = left_rotate(root->lchild);
        root = right_rotate(root);
    } else {
        if(root->rchild->rchild->h < root->rchild->lchild->h)
            root->rchild = right_rotate(root->rchild);
        root = left_rotate(root);
    }
    return root;
}

Node * insert(Node *root, int target){
    if(root == NIL)
        return getNewNode(target);
    if(root->val == target)
        return root;
    if(root->val > target)
        root->lchild = insert(root->lchild, target);
    else
        root->rchild = insert(root->rchild, target);
    update_height(root);
    return maintain(root);
}

Node * predecessor(Node *root){
    Node *temp = root->lchild;
    while(temp->rchild != NIL)
        temp = temp->rchild;
    return temp;
}

Node * erase(Node *root, int target){
    if(root == NIL) return NIL;
    if(root->val > target)
        root->lchild = erase(root->lchild, target);
    else if(root->val < target)
        root->rchild = erase(root->rchild, target);
    else {
        if(root->lchild == NIL || root->rchild == NIL){
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            free(root);
            return temp;
        } else{
            Node *temp = predecessor(root);
            root->val = temp->val;
            root->lchild = erase(root->lchild, root->val);
        }
    }
    update_height(root);
    return maintain(root);
}

void print(Node * root){
    printf("(%d[%d], %d, %d)\n",
            root->val, root->h,
            root->lchild->val,
            root->rchild->val
            );
    return;
}

void output(Node * root){
    if(root == NIL)
        return;
    output(root->lchild);
    print(root);
    output(root->rchild);
    return;
}



int main(){
    int op, val;
    Node *root = NIL;
    while(~scanf("%d%d", &op, &val)){
        switch(op){
            case 0: root = insert(root, val); break;
            case 1: root = erase(root, val); break;
        }
        output(root);
        printf("-----------\n");
    }

    return 0;
}
