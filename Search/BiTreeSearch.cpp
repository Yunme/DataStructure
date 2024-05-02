//
// Created by zzqni on 2024/4/27.
//

#include <vector>
#include <stack>
#include <fstream>
#include "BiTreeSearch.h"

void BST_inorder(const BSTree &tree, string &result) {
    if (!tree) return;
    BST_inorder(tree->lc, result);

    if (!result.empty()) {
        result += ",";
    }
    result += to_string(tree->data.key);

    BST_inorder(tree->rc, result);
}

void BST_inorder(const BSTree &tree) {
    BSTNode *current = tree;
    stack<BSTNode *> stack;
    bool first = true;
    while (current || !stack.empty()) {
        if (current) {
            stack.push(current);
            current = current->lc;
        } else {
            BSTNode *node = stack.top();
            stack.pop();
            if (first) first = false;
            else printf(",");
            printf("%d", node->data.key);
            current = node->rc;
        }
    }
}

void BST_TraversalInOrder(const BSTree &tree, vector<BSTNode *> *nodeOrder) {
    string result;
    printf("BST Traversal Inorder: ");
    BST_inorder(tree, result);
    printf("%s", result.c_str());
//    BST_inorder(tree);
    printf("\n");
//    if (!tree) return;
//    BST_TraversalInOrder(tree->lc, nodeOrder);
//    printf("%d,", tree->r.key);
//    if (nodeOrder)
//        nodeOrder->push_back(tree);
//    BST_TraversalInOrder(tree->rc, nodeOrder);
}

/**
* 二叉排序树 BST 插入元素 递归版本
*/
void BST_InsertRecursive(BSTree &tree, const ElementType &data) {
    if (!tree) {
        tree = new BSTNode;
        tree->data = data;
        tree->lc = tree->rc = nullptr;
        return;
    }
    if (data.key < tree->data.key) {
        BST_InsertRecursive(tree->lc, data);
    } else if (data.key > tree->data.key) {
        BST_InsertRecursive(tree->rc, data);
    }
}

/**
* 二叉排序树 BST 插入元素
*/
void BST_Insert(BSTree &tree, const ElementType &data) {
    auto *p = new BSTNode;
    p->data = data;
    p->lc = p->rc = nullptr;
    if (!tree) {
        tree = p;
        return;
    }
    BSTNode *parent = nullptr;
    BSTNode *current = tree;
    while (current) {
        parent = current;
        if (data.key < current->data.key) {
            current = current->lc;
        } else if (data.key > current->data.key) {
            current = current->rc;
        }
    }
    if (parent) {
        if (data.key < parent->data.key)
            parent->lc = p;
        else
            parent->rc = p;
    }
}

/**
 * 二叉排序树 BST 查找元素 递归版本
 */
BSTNode *BST_SearchRecursive(const BSTree &tree, KeyType key) {
    if (!tree || tree->data.key == key)
        return tree;
    if (key < tree->data.key) {
        BST_SearchRecursive(tree->lc, key);
    } else if (key > tree->data.key) {
        BST_SearchRecursive(tree->rc, key);
    }
}

/**
 * 二叉排序树 BST 查找元素
 */
BSTNode *BST_Search(BSTree &tree, KeyType key, int *searchCount) {
    BSTNode *current = tree;
    while (current) {
        (*searchCount)++;
        if (current->data.key == key) {
            return current;
        }
        if (key < current->data.key) {
            current = current->lc;
        } else if (key > current->data.key) {
            current = current->rc;
        }
    }
    return nullptr;
}

/**
 * 二叉排序树 BST 查找元素，并返回 parent
 */
BSTNode *BST_Search2(BSTree &tree, KeyType key, BSTNode *&parent) {
    BSTNode *current = tree;
    while (current) {
        if (current->data.key == key) {
            return current;
        }
        parent = current;
        if (key < current->data.key)
            current = current->lc;
        else
            current = current->rc;
    }
    return nullptr;
}

/**
 * 二叉排序树 BST 删除一个元素
 */
Status BST_Delete2(BSTree &tree, KeyType key) {
    BSTNode *parent = nullptr;
    BSTNode *current = tree;
    while (current) {
        if (current->data.key == key) {
            break;
        }
        parent = current;
        if (key < current->data.key) {
            current = current->lc;
        } else if (key > current->data.key) {
            current = current->rc;
        }
    }

    if (!current) return ERROR;

    // 被删结点有左右子树 两种方法：
    // 1. 删除当前结点中序遍历中的后继结点，当前结点被后继结点替换。
    // 2. 删除当前结点中序遍历中的前驱结点，当前结点被前驱结点替换。
    if (current->lc && current->rc) {
        // 寻找后继结点 也就是右子树中最小的结点
        BSTNode *successorParent = current;
        BSTNode *successor = current->rc;
        // 右子树中最小的结点在右子树的左子树上。
        while (successor->lc) {
            successorParent = successor;
            successor = successor->lc;
        }
        if (successorParent != current) {
            // 当前结点不是后继结点的直接前驱
            // 最小后继肯定无左子树，相当于删除只有右子树的结点
            successorParent->lc = successor->rc;
        } else {
            // 当前结点就是后继结点的前驱 且 后继结点无左子树，直接替换
            // 相当于删除只有右子树的结点
            successorParent->rc = successor->rc;
        }
        current->data = successor->data;
        delete successor;

        // 寻找前驱结点 也就是左子树中最大的结点
//        BSTNode *precursorParent = current;
//        BSTNode *precursor = current->lc;
//        // 左子树中最大的结点在左子树的右子树上。
//        while (precursor->rc) {
//            precursorParent = precursor;
//            precursor = precursor->rc;
//        }
//        // 当前结点就是前驱结点的父结点
//        if (precursorParent == current) {
//            precursorParent->lc = precursor->lc;
//        } else {
//            precursorParent->rc = precursor->lc;
//        }
//        current->r = precursor->r;
//        delete precursor;
    } else {
        // 被删结点有一个子树，或者是叶子结点
        BSTNode *child = nullptr;
        if (current->lc) {
            // 仅有左子树
            child = current->lc;
        } else if (current->rc) {
            // 仅有右子树
            child = current->rc;
        }
        if (!parent)
            // 被删的是根结点
            tree = child;
        else if (current == parent->lc)
            // 被删结点是父结点的左子树
            parent->lc = child;
        else if (current == parent->rc)
            // 被删结点是父结点的右子树
            parent->rc = child;
        delete current;
    }
    return OK;
}

/**
 * 二叉排序树 BST 删除元素
 */
Status BST_Delete(BSTree &tree, KeyType key) {
    BSTNode *parent = nullptr;
    BSTNode *current = BST_Search2(tree, key, parent);
    if (!current)
        return ERROR;
    if (current->lc && current->rc) {
        parent = current;
        BSTNode *successor = current->rc;
        while (successor->lc) {
            parent = successor;
            successor = successor->lc;
        }
        current->data = successor->data;
        current = successor;
    }
    BSTNode *child;
    if (!current->lc)
        child = current->rc;
    else
        child = current->lc;
    if (!parent)
        tree = child;
    else if (parent->lc == current)
        parent->lc = child;
    else
        parent->rc = child;
    delete current;
    return OK;
}

/**
 * 二叉排序树 BST 删除元素 递归版本
 */



int BST_getLevel(BSTree &tree, KeyType key) {
    BSTNode *node = tree;
    int level = 0;
    while (node) {
        if (node->data.key == key) {
            return level;
        }
        if (key < node->data.key)
            node = node->lc;
        else
            node = node->rc;
        level++;
    }
    return -1;
}

int BST_getLevelRecursive(BSTree &tree, KeyType key, int level) {
    if (!tree)
        return -1;
    if (tree->data.key == key)
        return level;

    if (key < tree->data.key) {
        return BST_getLevelRecursive(tree->lc, key, level + 1);
    } else {
        return BST_getLevelRecursive(tree->rc, key, level + 1);
    }
}

void generateDot(BSTNode *node, ofstream &dotFile) {
    if (node == nullptr) {
        return;
    }

    dotFile << node->data.key << ";\n";

    if (node->lc) {
        dotFile << node->data.key << " -> " << node->lc->data.key << " [label=\"L\"];\n";
    }

    if (node->rc) {
        dotFile << node->data.key << " -> " << node->rc->data.key << " [label=\"R\"];\n";
    }

    generateDot(node->lc, dotFile);
    generateDot(node->rc, dotFile);
}

void generateBSTImage(const BSTree &tree) {
    ofstream dotFile("bst.dot");
    dotFile << "digraph BinarySearchTree {\n";
    generateDot(tree, dotFile);
    dotFile << "}\n";
    dotFile.close();

    system(R"(C:\Users\zzqni\Downloads\Graphviz-10.0.1-win64\bin\dot.exe -Tpng -o binary_tree.png bst.dot)");
}