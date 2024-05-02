//
// Created by zzqni on 2024/4/21.
//

#include "testTree.h"

void testTree() {
//    testCommonTree();
//    testTree1();
    testBiTreeAlgorithm();
}

void testCommonTree() {
    BiTree tree;
    BiTree_Init(tree);
    // 先序
    const char *dlr = "ABD##E##C##";
//    const char *dlr = "AB##C##";
    BiTree_Create(tree, dlr);
//    BiTree_Cin_Create(tree);
    printf("先序遍历: ");
    BiTree_Traversal_DLR(tree);
    cout << endl;
    printf("中序遍历: ");
    BiTree_Traversal_LDR(tree);
    cout << endl;
    printf("后序遍历: ");
    BiTree_Traversal_LRD(tree);
    cout << endl;

    printf("中序遍历: ");
    BiTree_Traversal_Stack(tree);

    BiNode *p;
    BiTree_FindNode(tree, 'C', p);
    BiTree_Assign(tree, p, 'F');
    BiTree_Traversal_Stack(tree);

    BiNode *parent;
    BiTree_GetParent(tree, p, parent);
    BiTree_Assign(tree, parent, 'G');
    BiTree_Traversal_Stack(tree);

    // 左子树
    BiTree left;
    BiTree_FindNode(tree, 'G', p);
    BiTree_GetLeftChild(tree, p, left);
    BiTree_Traversal_Stack(left);

    // 右子树
    BiTree right;
    BiTree_FindNode(tree, 'G', p);
    BiTree_GetRightChild(tree, p, right);
    BiTree_Traversal_Stack(right);

    // 左兄弟
    BiTree_FindNode(tree, 'E', p);
    BiTree_GetLeftSibling(tree, p, left);
    BiTree_Traversal_Stack(left);

    // 右兄弟
    BiTree_FindNode(tree, 'D', p);
    BiTree_GetRightSibling(tree, p, right);
    BiTree_Traversal_Stack(right);

    // 插入结点
    BiTree_Traversal_Stack(tree);
    BiTree_InsertChild(tree, 'F', 1, 'H');
    BiTree_InsertChild(tree, 'F', 0, 'I');
    BiTree_Traversal_Stack(tree);

    BiTree_DeleteChild(tree, 'B', 1);
    BiTree_Traversal_Stack(tree);

    int depth = BiTree_GetDepth(tree);
    printf("tree depth: %d\n", depth);

    int count = BiTree_GetCount(tree);
    printf("tree node count: %d\n", count);

    count = BiTree_GetLeafCount(tree);
    printf("tree leaf count: %d\n", count);
}

void testTree1() {
    BiTree tree;
    BiTree_Init(tree);
//     先序
//    const char *dlr = "ABCD#E##F";
    const char *dlr = "ABC##DE#G##F###";
    BiTree_Create(tree, dlr);
//    BiTree_Traversal_Stack(tree);
    BiTree_Traversal_DLR(tree);
    cout << endl;
    BiTree_Traversal_Level(tree);

}
