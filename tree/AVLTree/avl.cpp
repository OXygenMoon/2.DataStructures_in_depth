#include <cstdio>
#include <iostream>
using namespace std;

#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define H(n) (n->h)

typedef struct Node{
	int key,h;
	struct Node *lchild, *rchild;
}Node;

//虚拟空节点, 为红黑树做准备的节点
Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL(){
	NIL->key = 0, NIL->h = 0;
	NIL->lchild = NIL->rchild = nullptr;
}
//优先初始化上面这一段代码


/*
 * AVL树的若干操作:
 * 1. 创建节点
 * 2. 销毁节点
 * 3. 插入
 * 4. 删除
*/

Node *getNewNode(int key){
	Node * tmp = (Node*)malloc(sizeof(Node));
	tmp->key = key;
	tmp->h = 1;
	tmp->lchild = NIL, tmp->rchild = NIL;
	return tmp;
}

void clear(Node * root){
	if(root == NIL)	return;
	clear(root->lchild);
	clear(root->rchild);
	free(root);
	return;
}

//调整高度
void update_height(Node * root){
	root->h = (H(L(root)) > H(R(root)) ? H(L(root)) : H(R(root))) + 1;
}

//左旋
Node * left_rotate(Node * root){
	Node * tmp = root->rchild; //新根节点
	root->rchild = tmp->lchild; //新左挂旧右
	tmp->lchild = root; //旧根挂新左
	update_height(root);
	update_height(tmp);
	return tmp;
}

//右旋
Node * right_rotate(Node * root){
	Node * tmp = root->lchild; //新根
	root->lchild = tmp->rchild; //新右成旧左
	tmp->rchild = root; //旧根成新左
	update_height(root);
	update_height(tmp);
	return tmp;
}

//调整
Node * maintain(Node * root){
	//平衡调整代码
	if(abs(H(L(root)) - H(R(root))) <= 1)	return root;
	if(root->lchild->h > root->rchild->h) {
		//LR先小左旋
		if(root->lchild->lchild->h < root->lchild->rchild->h)
			root->lchild = left_rotate(root->lchild);
		//LL大右旋
		root = right_rotate(root);
	} else {
		//RL先小右旋
		if(root->rchild->rchild->h < root->rchild->lchild->h)
			root->rchild = right_rotate(root->rchild);
		//RR大左旋
		root = left_rotate(root);
	}
	return root;
}

Node * insert(Node * root, int key){
	if(root == NIL)	return getNewNode(key);
	if(root->key == key)	return root;
	if(key < root->key)	root->lchild = insert(root->lchild, key);
	if(key > root->key)	root->rchild = insert(root->rchild, key);
	update_height(root);
	return maintain(root);
}

//寻找前驱节点,默认传入度为2的节点,前父节点有左子树
Node * predeccessor(Node * root){
	Node * tmp = root->lchild;
	while(tmp->rchild)	tmp = tmp->rchild;
	return tmp;
}

Node * erase(Node * root, int key){
	if(root == NIL)	return NIL;
	if(key < root->key) {
		root->lchild = erase(root->lchild, key);
	} else if(key > root->key) {
		root->rchild = erase(root->rchild, key);
	} else { //删除当前节点
		if(root->rchild == NIL || root->lchild == NIL){
			Node * tmp = root->rchild != NIL ? root->rchild : root->lchild;
			free(root);
			return tmp;
		} else { // 删除度为2的节点
			Node * tmp = predeccessor(root);
			root->key = tmp->key;
			root->lchild = erase(root->lchild, root->key);
		}
	}
	update_height(root);
	return maintain(root);
}

void print(Node * root){
	printf("(%d[%d], %d, %d)\n",
			root->key, root->h,
			root->lchild->key,
			root->rchild->key
			);
}


void output(Node * root){
	if(root == NIL)	return;
	print(root);
	output(root->lchild);
	output(root->rchild);
	return ;
}

int main(int argc, char ** argv){
	int op, val;
	Node* root = NIL;
	while(~scanf("%d%d", &op, &val)){
		switch(op){
			case 0: root = erase(root, val); break;
			case 1: root = insert(root, val); break;
		}
		output(root);
		printf("------------\n");
	}
	return 0;
}
