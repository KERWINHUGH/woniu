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

// 使用后续遍历回收资源
void destroy(BiTNode *root){
    if(root == NULL) return;
    destroy(root->lchild);
    destroy(root->rchild);
    free(root);
}

int getDepth(BiTNode *root){
    if(root == NULL) return 0;
    // 递归求解左右子树深度
    int leftDepth = getDepth(root->lchild);
    int rightDepth = getDepth(root->rchild);
    return leftDepth > rightDepth ? leftDepth+1 : rightDepth+1;
}

int main(){
    // 创建如下二叉树
    //                      1
    //                   /    \
    //                 2       3
    //               /   \    /  \
    //              4     5  6    7
    //             / \   / \
    //            8   9 10  11
    //                   \
    //                    12
    BiTNode *root = createBiTree(1);
    root->lchild = createBiTree(2);
    root->rchild = createBiTree(3);
    root->lchild->lchild = createBiTree(4);
    root->lchild->rchild = createBiTree(5);
    root->rchild->lchild = createBiTree(6);
    root->rchild->rchild = createBiTree(7);
    root->lchild->lchild->lchild = createBiTree(8);
    root->lchild->lchild->rchild = createBiTree(9);
    root->lchild->rchild->lchild = createBiTree(10);
    root->lchild->rchild->rchild = createBiTree(11);
    root->lchild->rchild->lchild->rchild = createBiTree(12);
    printf("最大深度为：%d\n", getDepth(root));
    destroy(root);
}