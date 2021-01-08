#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
using namespace std;

#define KEY(n)    (n ? n->key : 0)
#define SIZE(n)   (n ? n->size : 0)
#define L(n)      (n ? n->lchild : 0)

typedef struct Node{
	int key, size;
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

/*
 * 优化1: 将删除度为0和度为1的节点的代码合并
 * 优化2: 实现查找第k位的元素
 * 优化3: 实现输出前k位的元素(TOP-K)
*/

void update_size(Node * root){
	root->size = SIZE(root->lchild) + SIZE(root->rchild) + 1;
}

Node * getNewNode(int key){
	Node *p = (Node *)malloc(sizeof(Node));
	p->key = key;
	p->size = 1;
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

int search_k(Node * root, int k){
	if(root == nullptr)	return -1;
	if(SIZE(L(root)) == k - 1)	return root->key;
	if(k <= SIZE(L(root)))	{
		return search_k(root->lchild, k);
	} else {
		return search_k(root->rchild, k - SIZE(L(root)) - 1);
	}
}


Node * insert(Node * root, int val){
	if(root == nullptr)	    return getNewNode(val);
	if(root->key == val)	return root;
	if(val < root->key)     root->lchild = insert(root->lchild, val);
	if(val > root->key)     root->rchild = insert(root->rchild, val);
	update_size(root);	
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
		   //删除度为0的节点和度为1的节点操作相同 
		if(root->lchild == nullptr || root->rchild == nullptr){
			Node * tmp = root->lchild ? root->lchild : root->rchild;
			free(root);
			return tmp;
		} else { //删除度为2的节点
			Node * tmp = predecessor(root);
			root->key = tmp->key;
			root->lchild = erase(root->lchild, tmp->key);
		}
	}
	update_size(root);
	return root;
}


void output(Node * root){
	if(root == nullptr)	return;
	output(root->lchild);
	printf("[%d, %d, %d, size : %d]\n",KEY(root),KEY(root->lchild),KEY(root->rchild),SIZE(root));
	output(root->rchild);
	return;
}

void output_k(Node *root, int k){
	if(k == 0 || root == nullptr)	return;
	if(k <= SIZE(L(root))){
		output_k(root->lchild, k);
	} else {
		output(root->lchild);
		printf("[%d, %d, %d, size : %d]\n",KEY(root),KEY(root->lchild),KEY(root->rchild),SIZE(root));
		output_k(root->rchild, k - SIZE(L(root)) - 1);
	}
	return;
}


int main(int argc, char ** argv){
	
	int op, val;
	
	/* op :
	 * 0 查找
	 * 1 插入
	 * 2 删除
	 * 3 查找第k位的元素
	 * 4 输出前k位的元素
	*/
	Node * root = nullptr;
	while(~scanf("%d%d", &op, &val)){
		switch(op){
			case 0: printf("search %d, result : %d\n", val, search(root, val)); break;
			case 1: root = insert(root, val); break;
			case 2: root = erase(root, val); break;
			case 3: printf("search k %d, result : %d\n",val, search_k(root, val)); break;
			case 4: {
						printf("output top-%d elements\n",val);
						output_k(root, val);
						printf("----------------\n");
					} break;
		}
		if(op != 0 && op != 4){
			output(root);
			printf("----------------\n");
		}
	}
	
	return 0;
}
