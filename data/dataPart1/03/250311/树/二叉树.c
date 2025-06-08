#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode;

BiTNode *createBiTree(int data) {
    BiTNode *node = (BiTNode *) malloc(sizeof(BiTNode));
    node->data = data;
    // printf("当前节点数据为: %d\n", data);
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

/*
先序遍历
1. 先访问根节点
2. 先序遍历左子树
3. 先序遍历右子树
以下面的二叉树为例，其线序遍历过程为：
1. 访问根节点   1
2. 进入根节点的左子树
    - 访问节点2  2
    - 进入节点2的左子树
    - 访问节点4  4
    - 节点4没有孩子节点，访问结束
    - 进入节点2的右子树
    - 访问节点5  5
    - 节点5没有孩子节点，访问结束
3. 进入根节点的右子树
    - 访问节点3  3
    - 进入节点3的左子树
    - 访问节点6  6
    - 节点6没有孩子节点，访问结束
    - 进入节点3的右子树
    - 访问节点7  7
    - 节点7没有孩子节点，访问结束
4. 遍历结果：1 2 4 5 3 6 7
*/
void preOrder(BiTNode *root){
    if(root == NULL) return;    // 递归终止条件
    printf("%d ", root->data);  // 打印当前节点数据
    preOrder(root->lchild);     // 递归遍历左子树
    preOrder(root->rchild);     // 递归遍历右子树
}

/*
中序遍历：先遍历左子树，再访问根节点，最后遍历右子树
1. 进入节点1的左子树
    - 进入节点2的左子树
        - 进入节点4的左子树，但是节点4没有左子树，结束
        - 访问节点4
        - 进入节点4的右子树，但是节点4没有右子树，结束
    - 访问节点2
    - 进入节点2的右子树
        - 进入节点5的左子树，但是节点5没有左子树，结束
        - 访问节点5
        - 进入节点5的右子树，但是节点5没有右子树，结束
2. 访问节点1
3. 进入节点1的右子树
    - 进入节点3的左子树
        - 进入节点6的左子树，但是节点6没有左子树，结束
        - 访问节点6
        - 进入节点6的右子树，但是节点6没有右子树，结束
    - 访问节点3
    - 进入节点3的右子树
        - 进入节点7的左子树，但是节点7没有左子树，结束
        - 访问节点7
        - 进入节点7的右子树，但是节点7没有右子树，结束
4. 中序遍历结果：4 2 5 1 6 3 7
*/
void inOrder(BiTNode *root){
    if(root == NULL) return;    // 递归终止条件
    inOrder(root->lchild);     // 递归遍历左子树
    printf("%d ", root->data);  // 打印当前节点数据
    inOrder(root->rchild);     // 递归遍历右子树
}

/*
后续遍历：先遍历左子树，再遍历右子树，最后访问根节点
1. 进入节点1的左子树
    - 进入节点2的左子树
        - 进入节点4的左子树，节点4没有左子树，结束
        - 进入节点4的右子树，节点4没有右子树，结束
        - 访问节点4
    - 进入节点2的右子树
        - 进入节点5的左子树，节点5没有左子树，结束
        - 进入节点5的右子树，节点5没有右子树，结束
        - 访问节点5
    - 访问节点2
2. 进入节点1的右子树
    - 进入节点3的左子树
        - 进入节点6的左子树，节点6没有左子树，结束
        - 进入节点6的右子树，节点6没有右子树，结束
        - 访问节点6
    - 进入节点3的右子树
        - 进入节点7的左子树，节点7没有左子树，结束
        - 进入节点7的右子树，节点7没有右子树，结束
        - 访问节点7
    - 访问节点3
3. 访问节点1
4. 后续遍历结果为：4 5 2 6 7 3 1
*/
void postOrder(BiTNode *root){
    if(root == NULL) return;    // 递归终止条件
    postOrder(root->lchild);     // 递归遍历左子树
    postOrder(root->rchild);     // 递归遍历右子树
    printf("%d ", root->data);  // 打印当前节点数据
}

// 使用后续遍历回收资源
void destroy(BiTNode *root){
    if(root == NULL) return;
    destroy(root->lchild);
    destroy(root->rchild);
    free(root);
}

int main(){
    // 创建如下的二叉树
    //             1
    //            / \
    //           2   3
    //          / \  / \
    //         4   56   7
    BiTNode *root = createBiTree(1);    // 创建根节点
    // 创建根节点的左孩子和右孩子节点
    root->lchild = createBiTree(2);
    root->rchild = createBiTree(3);
    // 创建左子树的左孩子和右孩子节点
    root->lchild->lchild = createBiTree(4);
    root->lchild->rchild = createBiTree(5);
    // 创建右子树的左孩子和右孩子节点
    root->rchild->lchild = createBiTree(6);
    root->rchild->rchild = createBiTree(7);
    printf("先序遍历二叉树：");
    preOrder(root);
    printf("\n");
    printf("中序遍历二叉树：");
    inOrder(root);
    printf("\n");
    printf("后序遍历二叉树：");
    postOrder(root);
    printf("\n");
    destroy(root);
    return 0;
}