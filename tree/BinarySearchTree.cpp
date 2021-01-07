#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
using namespace std;

#define KEY(n) (n ? n->key : 0)



typedef struct Node{
	int key;
	struct Node *lchild, *rchild;
}Node;

/*
 * 二叉搜索树的若干操作:
 * 1. 创建节点
 * 2. 销毁节点
 * 3. 查找
 * 4. 插入
 * 5. 删除
*/

Node * getNewNode(int key){
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->lchild = nullptr, p->rchild = nullptr;
	return p;
}

void clear(Node * root){
	if(root == nullptr)	return;
	clear(root->lchild);
	clear(root->rchild);
	free(root);
	return;
}

int search(Node* root, int val){
	if(root == nullptr)		return 0;
	if(root->key == val)	return 1;
	if(root->key > val)		return search(root->lchild, val);
	if(root->key < val)	    return search(root->rchild, val);
	return 0;
}

Node * insert(Node * root, int val){
	if(root == nullptr)	    return getNewNode(val);
	if(root->key == val)	return root;
	if(val < root->key)     root->lchild = insert(root->lchild, val);
	if(val > root->key)     root->rchild = insert(root->rchild, val);
	return root;
}

Node * predecessor(Node * root){
	Node * tmp = root->lchild;
	while(tmp->rchild != nullptr)	tmp = tmp->rchild;
	return tmp;
}

Node * erase(Node * root, int val){
	if(root == nullptr)	    return nullptr;
	if(root->key > val)
		root->lchild = erase(root->lchild, val);
	else if(root->key < val)
		root->rchild = erase(root->rchild, val);
	else { //删除节点本身
		if(root->lchild == nullptr && root->rchild == nullptr){
			free(root);
			return nullptr;
		} else if(root->lchild == nullptr || root->rchild == nullptr){
			Node * tmp = root->lchild ? root->lchild : root->rchild;
			free(root);
			return tmp;
		} else { //删除度为2的节点
			Node * tmp = predecessor(root);
			root->key = tmp->key;
			root->lchild = erase(root->lchild, tmp->key);
		}
	}
	return root;
}

void output(Node * root){
	if(root == nullptr)	return;
	output(root->lchild);
	printf("[%d, %d, %d]\n",KEY(root),KEY(root->lchild),KEY(root->rchild));
	output(root->rchild);
	return;
}




int main(int argc, char ** argv){
	
	int op, val;
	
	/* op :
	 * 0 查找
	 * 1 插入
	 * 2 删除
	*/
	Node * root = nullptr;
	while(~scanf("%d%d", &op, &val)){
		switch(op){
			case 0: printf("search %d, result : %d\n", val, search(root, val)); break;
			case 1: root = insert(root, val); break;
			case 2: root = erase(root, val); break;
		}
		if(op){
			output(root);
			printf("----------------\n");
		}
	}
	
	return 0;
}
