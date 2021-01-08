## AVL树

名称 : AVL树

发明者 : 

G. M. Adelson-Velsky

E.M. Landis

年代 : 1962年(58岁)

性质 : 

| H(left) - H(right) | ≤ 1

优点 :

由于对每个节点的左右子树的树高做了限制, 所以整棵树不会退化成一个链表

### 学习重点

1. 平衡二叉排序树,本质上也是二叉排序树, 所以拥有二叉排序树的所有性质
2. 平衡二叉排序树的学习重点, 在于平衡条件以及平衡调整的相关学习

### 性质

1. 平衡条件 : | H(left) - H(right) | ≤ 1

### 思考

高度为 H 的树, 所包含节点的范围是?

BinarySearchTree : H ≤ size ≤ 2^H - 1

AVLTree : low(H-2) + low(H-1) + 1 ≤ size ≤ 2^H - 1 (low(H) 是 H 高度的二叉树的最少节点数) 左边等于 1.5^H

### 操作

**AVL树 - 左旋**

<img src="https://i.loli.net/2021/01/08/3XlUQLIxHNKTCt5.png"/>

<img src="https://i.loli.net/2021/01/08/IxZvkmGhcprAE42.png"/>

**AVL树 - 右旋**

<img src="https://i.loli.net/2021/01/08/oNYgrvHhOSkb9BK.png"/>

<img src="https://i.loli.net/2021/01/08/vcLKAlOEMu7hRaq.png"/>

### 失衡类型

h(1,2,3,4) 分别代表左孩子的左子树个高,左孩子的右子树高,右孩子的左子树高和右孩子的右子树高

LL类型:左子树的左孩子更高

满足条件 : h1 = max(h3, h4) + 2 = h2 + 1

调整方案 : K1 右旋

LR类型:左子树的右孩子更高

满足条件 : max(h2, h3) = h4 = h1

调整方案 : 小左旋, 大右旋(左孩子左旋, 根节点右旋)

RL类型:右子树的左孩子更高

调整方案 : 小右旋, 大左旋

RR类型:右子树的右孩子更高

调整方案 : K1 左旋

### 平衡调整策略

1. 发生在回溯阶段的, 第一个失衡节点处
2. 理解平衡调整策略的关键在于 : 分析清楚四种情况下, ABCD四棵子树树高的关系
3. LL, 大右旋
4. LR, 先小左旋, 再大右旋
5. RL, 先小右旋, 再大左旋
6. RR, 大左旋

### 代码关键点

1. 插入和删除以后, 注意调整树高字段, 先调低的root, 再调高的tmp
2. 引入了NIL节点, 代替了 NULL和nullptr, NULL不可访问资源, NIL是一个实际节点, 可以访问资源(h,lchild,rchild)
