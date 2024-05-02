//
// Created by zzqni on 2024/4/26.
//

#include "testSearch.h"
#include <random>
#include <algorithm>

vector<ElementType> getRandomDataArray() {
    int count = 20;
    vector<ElementType> data(count);
    random_device rd;
    mt19937 generator(rd());

    for (int i = 0; i < count; ++i) {
        uniform_int_distribution<int> distribution(i * 10, (i + 1) * 10);
        int randomNumber = distribution(generator);
        ElementType e;
        e.key = randomNumber;
        e.info = "";
        data[i] = e;
    }
    return data;
}

vector<ElementType> fixedData() {
//    const int count = 20;
    int count;
//    int array[count] = {81, 68, 32, 1, 4, 25, 94, 64, 30, 71, 85,
//                        24, 70, 62, 28, 54, 31, 43, 53, 20};
//    int array[] = {60, 70, 80, 90, 100};
//    int array[count] = {70, 60, 65, 90, 100};
    int array[] = {10, 5, 15, 3, 7, 18, 12, 20};
//    int array[] = {588, 3, 699, 928, 834, 764, 526, 235, 919, 899, 182, 983, 817, 149, 897, 371, 833, 910, 165, 431, 119,
//               671, 902, 838, 444, 359, 211, 484, 327, 898, 292, 4, 84, 366, 940, 627, 123, 851, 274, 736, 523, 541,
//               913, 905, 191, 137, 791, 197, 583, 498};
    count = size(array);
    vector<ElementType> data(count);
    for (int i = 0; i < count; ++i) {
        data[i].key = array[i];
    }
    return data;
}

void testSqSearch() {
    SqSearchCommon();
    SqSearchSentinel();

    vector<ElementType> data = getRandomDataArray();
    // 模拟查找
    KeyType key = data[12].key;
    int index = SqSearchBinary(data, key);
    printf("Binary Search: %d\n", index);

    key = data[15].key;
    index = SqSearchBinaryRecursive(data, key, 0, data.size() - 1);
    printf("Binary Search: %d\n", index);
}

void testBSTSearch() {
    // 插入元素
    BSTree tree = nullptr;
    vector<ElementType> data = getDataArrayForSort();
    // 递归 插入元素
    for (const ElementType &e: data) {
        printf("%d,", e.key);
        BST_InsertRecursive(tree, e);
    }
    printf("\n");
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");
    tree = nullptr;
    data = getDataArrayForSort();
    // 非递归 插入元素
    for (const ElementType &e: data) {
        printf("%d ", e.key);
        BST_Insert(tree, e);
    }
    printf("\n");
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);


    // 模拟查找
    printf("\n");
    KeyType key = data[12].key;
    // 递归 查找
    BSTNode *p = BST_SearchRecursive(tree, key);
    if (p)
        printf("BST Search found key:%d\n", p->data.key);
    else
        printf("BST Search not found for key:%d\n", key);
    key = data[12].key;
    // 非递归 查找
    p = BST_Search(tree, key);
    if (p)
        printf("BST Search found key:%d\n", p->data.key);
    else
        printf("BST Search not found for key:%d\n", key);

}

void testSearchBSTDelete() {
    printf("BST delete:\n");
    vector<ElementType> data = fixedData();
    BSTree tree = nullptr;
    for (const ElementType &e: data) {
        printf("%d,", e.key);
        BST_Insert(tree, e);
    }
    printf("\n");

    KeyType key;
    key = 28;
    int level = BST_getLevelRecursive(tree, key);
    printf("%d at level: %d\n", key, level);

    // 删除元素
    // 删除叶子结点
    key = 70;
    Status s = BST_Delete(tree, key);
    if (s)
        printf("delete key:%d success!\n", key);
    else
        printf("delete key:%d failed!\n", key);
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");

    // 删除仅有左子树的结点
    key = 64;
    s = BST_Delete(tree, key);
    if (s)
        printf("delete key:%d success!\n", key);
    else
        printf("delete key:%d failed!\n", key);
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");

    // 删除仅有右子树的结点
    key = 1;
    s = BST_Delete(tree, key);
    if (s)
        printf("delete key:%d success!\n", key);
    else
        printf("delete key:%d failed!\n", key);
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");

    // 删除左右子树都有的结点
    key = 25;
    s = BST_Delete(tree, key);
    if (s)
        printf("delete key:%d success!\n", key);
    else
        printf("delete key:%d failed!\n", key);
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");

    // 删除左右子树都有的结点
    key = 32;
    s = BST_Delete(tree, key);
    if (s)
        printf("delete key:%d success!\n", key);
    else
        printf("delete key:%d failed!\n", key);
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");

    // 删除根结点
    key = 81;
    s = BST_Delete(tree, key);
    if (s)
        printf("delete key:%d success!\n", key);
    else
        printf("delete key:%d failed!\n", key);
    printf("BST Traversal Inorder: ");
    BST_TraversalInOrder(tree);
    printf("\n");
}

void testAVLSearch() {
    AVLTree avlTree = nullptr;
    BSTree bsTree = nullptr;
    int dataCount = 1000;

    vector<ElementType> data = getDataArrayForSort(dataCount, 100000);
//    vector<ElementType> r = fixedData();
    for (const ElementType &e: data) {
//        printf("%d", e.key);
//        if (e.key != r.back().key) {
//            printf(",");
//        }
        BST_Insert(bsTree, e);
//        AVL_InsertNodeRecursive(avlTree, e);
        AVL_InsertNode(avlTree, e);
    }
    printf("\n");
    AVL_InorderTraversal(avlTree);
//    BST_TraversalInOrder(bsTree);

    int searchCount = 0;
    KeyType searchKey = data[data.size() / 2].key;
    AVLNode *node = AVL_Search(avlTree, searchKey, &searchCount);
    if (node) {
        printf("AVL search found %d, count:%d\n", searchKey, searchCount);
    } else
        printf("AVL search not found\n");
    searchCount = 0;
    BSTNode *bstNode = BST_Search(bsTree, searchKey, &searchCount);
    if (bstNode) {
        printf("BST search found %d, count:%d\n", searchKey, searchCount);
    } else
        printf("BST search not found\n");

    searchCount = 0;
    KeyType deleteKey = data[data.size() / 3].key;
//    KeyType deleteKey = r[7].key;
//    AVL_DeleteNodeRecursive(avlTree, deleteKey);
    AVL_DeleteNode(avlTree, deleteKey);
    node = AVL_Search(avlTree, deleteKey, &searchCount);
    AVL_InorderTraversal(avlTree);
    if (node) {
        printf("After Delete AVL search found %d, count:%d\n", deleteKey, searchCount);
    } else
        printf("After Delete AVL search not found\n");
//    generateBSTImage(bsTree);
    generateAVLImage(avlTree);
}

void testRedBlackTree() {
    AVLTree avlTree = nullptr;
    RedBlackTree tree = nullptr;
    int dataCount = 50;
//    vector<ElementType> r = getDataArrayForSort(dataCount, 1000);
    vector<ElementType> data = fixedData();
    for (const ElementType &e: data) {
        printf("%d", e.key);
        if (e.key != data.back().key) {
            printf(",");
        }
        RedBlack_InsertNode(tree, e);
        AVL_InsertNode(avlTree, e);
    }
    printf("\n");
    RedBlack_Traversal(tree);

    int searchCount = 0;
    KeyType searchKey = data[data.size() / 2].key;
    RBNode *node = RedBlack_Search(tree, searchKey, searchCount);
    if (node) {
        printf("RedBlackTree search found %d, count:%d\n", searchKey, searchCount);
    } else
        printf("RedBlackTree search not found\n");
    searchCount = 0;
    AVLNode *avlNode = AVL_Search(avlTree, searchKey, &searchCount);
    if (avlNode) {
        printf("AVL search found %d, count:%d\n", searchKey, searchCount);
    } else
        printf("AVL search not found\n");
    searchCount = 0;
//    KeyType deleteKey = r[r.size() / 3].key;
    KeyType deleteKey = 671;
    AVL_DeleteNode(avlTree, deleteKey);
    printf("Delete RedBlackTree key:%d\n", deleteKey);
    RedBlack_DeleteNode(tree, deleteKey);
    node = RedBlack_Search(tree, deleteKey, searchCount);
    RedBlack_Traversal(tree);
//    AVL_InorderTraversal(avlTree);
    if (node) {
        printf("After Delete RedBlackTree search found %d, count:%d\n", deleteKey, searchCount);
    } else
        printf("After Delete RedBlackTree search not found\n");
//    generateAVLImage(avlTree);
    generateRedBlackTreeImage(tree);
}

void testHashTable() {
    HashTable hashTable;
    int dataCount = 50;
    vector<ElementType> data = getDataArrayForSort(dataCount, 500);
//    vector<ElementType> r = fixedData();
    for (const ElementType &e: data) {
        printf("%d", e.key);
        if (e.key != data.back().key) {
            printf(",");
        }
        HashTable_Insert(hashTable, e);
    }
    printf("\n");
    HashTable_Print(hashTable);
    KeyType searchKey = data[data.size() / 2].key;
    ElementType result;
    if (HashTable_Search(hashTable, searchKey, result)) {
        printf("HashTable search found %d\n", searchKey);
    } else
        printf("HashTable search not found\n");
    searchKey = data[data.size() / 2].key;
    HashTable_Delete(hashTable, searchKey, result);
    if (HashTable_Search(hashTable, searchKey, result)) {
        printf("After delete HashTable search found %d\n", searchKey);
    } else
        printf("After delete HashTable search not found %d\n", searchKey);
    HashTable_Print(hashTable);
}


void testSearch() {
//    testSqSearch();
//    testBSTSearch();
//    testSearchBSTDelete();
//    testAVLSearch();
//    testRedBlackTree();
    testHashTable();
}