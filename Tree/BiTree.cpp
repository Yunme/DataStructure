//
// Created by zzqni on 2024/4/21.
//

#include <stack>
#include <queue>
#include "BiTree.h"

void BiTree_Init(BiTree &tree) {
//    tree->r = '\0';
//    tree->rc = nullptr;
//    tree->lc = nullptr;
}

void BiTree_Cin_Create(BiTree &tree) {
    char a;
    cin >> a;
    if (a == '#') {
        tree = nullptr;
        return;
    }
    tree = new BiNode;
    tree->data = a;
    BiTree_Cin_Create(tree->lc);
    BiTree_Cin_Create(tree->rc);
}

void BiTree_Create(BiTree &tree, const char *&array) {
    if (*array != '\0') {
        char a = *array;
        if (a == '#') {
            tree = nullptr;
            return;
        }
        tree = new BiNode;
        tree->data = a;
        BiTree_Create(tree->lc, ++array);
        BiTree_Create(tree->rc, ++array);
    }
}

/**
 * 先序遍历，递归版本
 */
void BiTree_Traversal_DLR(BiTree tree) {
    if (!tree) {
        return;
    }
    printf("%c", tree->data);
    BiTree_Traversal_DLR(tree->lc);
    BiTree_Traversal_DLR(tree->rc);
}

/**
 * 中序遍历，递归版本
 */
void BiTree_Traversal_LDR(BiTree tree) {
    if (!tree) {
        return;
    }
    BiTree_Traversal_LDR(tree->lc);
    printf("%c", tree->data);
    BiTree_Traversal_LDR(tree->rc);
}

/**
 * 后序遍历，递归版本
 */
void BiTree_Traversal_LRD(BiTree tree) {
    if (!tree) {
        return;
    }
    BiTree_Traversal_LRD(tree->lc);
    BiTree_Traversal_LRD(tree->rc);
    printf("%c", tree->data);
}

/**
 * 中序遍历 非递归版本
 */
void BiTree_Traversal_Stack(BiTree tree) {
    stack<BiTree> stack;
    BiNode *t = tree;
    while (t || !stack.empty()) {
        if (t) {
            stack.push(t);
            t = t->lc;
        } else {
            printf("%c", stack.top()->data);
            stack.pop();
            t = stack.top()->rc;
        }
    }
    printf("\n");
}

/**
 * 层次遍历
 */
void BiTree_Traversal_Level(BiTree tree) {
    queue<BiTree> q;
    q.push(tree);
    while (!q.empty()) {
        BiTree p = q.front();
        printf("%c", p->data);
        q.pop();
        if (p->lc)
            q.push(p->lc);
        if (p->rc)
            q.push(p->rc);
    }
    printf("\n");
}

/**
 * 树的深度
 */
int BiTree_GetDepth(BiTree tree) {
    if (!tree) {
        return 0;
    }
    int m = BiTree_GetDepth(tree->lc);
    int n = BiTree_GetDepth(tree->rc);
    return m > n ? m + 1 : n + 1;
}

/**
 * 树的结点总数
 */
int BiTree_GetCount(BiTree tree) {
    if (!tree) {
        return 0;
    }
    return BiTree_GetCount(tree->lc) + BiTree_GetCount(tree->rc) + 1;
}

int BiTree_GetLeafCount(BiTree tree) {
    if (!tree) {
        return 0;
    }
    if (!tree->rc && !tree->lc) {
        return 1;
    }
    return BiTree_GetLeafCount(tree->lc) + BiTree_GetLeafCount(tree->rc);
}

void BiTree_FindNode(BiTree tree, ElemType e, BiNode *&node) {
    if (tree) {
        if (tree->data == e) {
            node = tree;
            return;
        }
        BiTree_FindNode(tree->lc, e, node);
        BiTree_FindNode(tree->rc, e, node);
    }
}

/**
 * 树上某个结点赋值
 */
void BiTree_Assign(BiTree tree, BiNode *&node, ElemType e) {
    node->data = e;
}

/**
 * 寻找双亲结点
 */
void BiTree_GetParent(BiTree tree, BiNode *search, BiNode *&parent) {
    if (tree) {
        if (tree->lc == search || tree->rc == search) {
            parent = tree;
            return;
        }
        BiTree_GetParent(tree->lc, search, parent);
        BiTree_GetParent(tree->rc, search, parent);
    }
}

/**
 * 寻找左子树
 */
void BiTree_GetLeftChild(BiTree tree, BiNode *search, BiTree &leftChild) {
    if (tree) {
        if (tree == search) {
            leftChild = tree->lc;
            return;
        }
        BiTree_GetLeftChild(tree->lc, search, leftChild);
        BiTree_GetLeftChild(tree->rc, search, leftChild);
    }
}

/**
 * 寻找右子树
 */
void BiTree_GetRightChild(BiTree tree, BiNode *search, BiTree &rightChild) {
    if (tree) {
        if (tree == search) {
            rightChild = tree->rc;
            return;
        }
        BiTree_GetRightChild(tree->lc, search, rightChild);
        BiTree_GetRightChild(tree->rc, search, rightChild);
    }
}

/**
 * 寻找左兄弟
 */
void BiTree_GetLeftSibling(BiTree tree, BiNode *search, BiTree &leftSibling) {
    if (tree) {
        if (tree->rc == search) {
            leftSibling = tree->lc;
            return;
        }
        BiTree_GetLeftSibling(tree->lc, search, leftSibling);
        BiTree_GetLeftSibling(tree->rc, search, leftSibling);
    }
}

/**
 * 寻找右兄弟
 */
void BiTree_GetRightSibling(BiTree tree, BiNode *search, BiTree &rightSibling) {
    if (tree) {
        if (tree->lc == search) {
            rightSibling = tree->rc;
            return;
        }
        BiTree_GetRightSibling(tree->lc, search, rightSibling);
        BiTree_GetRightSibling(tree->rc, search, rightSibling);
    }
}

/**
 * 插入结点
 */
void BiTree_InsertChild(BiTree &tree, ElemType search, int LR, ElemType e) {
    BiNode *p;
    BiTree_FindNode(tree, search, p);
    if (!p) return;
    BiNode *node = new BiNode;
    node->data = e;
    if (LR) {
        node->lc = p->lc;
        p->lc = node;
    } else {
        node->rc = p->rc;
        p->rc = node;
    }
}

/**
 * 删除 结点 的左或右孩子
 */
void BiTree_DeleteChild(BiTree &tree, ElemType search, int LR) {
    BiNode *p;
    BiTree_FindNode(tree, search, p);
    if (!p) return;
    if (LR) {
        p->lc = nullptr;
        delete p->lc;
    } else {
        p->rc = nullptr;
        delete p->rc;
    }
}