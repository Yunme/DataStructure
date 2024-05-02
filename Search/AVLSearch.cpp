//
// Created by zzqni on 2024/4/28.
//

#include "AVLSearch.h"
#include <stack>
#include <fstream>

void AVL_InorderTraversal(const AVLTree &tree) {
    AVLNode *current = tree;
    stack<AVLNode *> stack;
    bool first = true;
    printf("AVL Traversal Inorder: ");
    while (current || !stack.empty()) {
        if (current) {
            stack.push(current);
            current = current->lc;
        } else {
            AVLNode *node = stack.top();
            stack.pop();
            if (abs(AVL_getBalanceFactor(node)) > 1) {
                if (first) first = false;
                else printf(",");
                printf("%d:(%d)", node->data.key, AVL_getBalanceFactor(node));
            }

            current = node->rc;
        }
    }
    printf("\n");
}

AVLNode *AVL_newNode(const ElementType &element) {
    auto *node = new AVLNode;
    node->data = element;
    node->lc = node->rc = nullptr;
    node->height = 1;
    return node;
}

int AVL_getHeight(AVLNode *node) {
    if (node) return node->height;
    return 0;
}

void AVL_UpdateHeight(AVLNode *&node) {
    node->height = 1 + max(AVL_getHeight(node->lc), AVL_getHeight(node->rc));
}

/**
 * 左旋 (RR)
 * 1. 当前结点右子树作为新树的根结点
 * 2. 新根的左子树作为旧根的右子树
 * 3. 当前结点作为新树根的左子树
 * @param node 失衡的结点
*/
AVLNode *AVL_rotateLeft(AVLNode *node) {
    AVLNode *newRoot = node->rc;
    node->rc = newRoot->lc;
    newRoot->lc = node;

    AVL_UpdateHeight(node);
    AVL_UpdateHeight(newRoot);
    return newRoot;
}

/**
 * 右旋(LL)
 * @param node 失衡的结点
 */
AVLNode *AVL_rotateRight(AVLNode *node) {
    AVLNode *newRoot = node->lc;
    node->lc = newRoot->rc;
    newRoot->rc = node;

    AVL_UpdateHeight(node);
    AVL_UpdateHeight(newRoot);
    return newRoot;
}

int AVL_getBalanceFactor(AVLNode *node) {
    return AVL_getHeight(node->lc) - AVL_getHeight(node->rc);
}

void AVL_Balance(AVLNode *&node) {
    // 计算平衡因子
    int balance = AVL_getBalanceFactor(node);
    // LL 右旋
    if (balance > 1 && AVL_getBalanceFactor(node->lc) > 0)
        node = AVL_rotateRight(node);
        // LR 左旋左子树，右旋结点
    else if (balance > 1 && AVL_getBalanceFactor(node->lc) < 0) {
        node->lc = AVL_rotateLeft(node->lc);
        node = AVL_rotateRight(node);
    }
        // RR 左旋
    else if (balance < -1 && AVL_getBalanceFactor(node->rc) < 0)
        node = AVL_rotateLeft(node);
        // RL 右旋右子树 左旋结点
    else if (balance < -1 && AVL_getBalanceFactor(node->rc) > 0) {
        node->rc = AVL_rotateRight(node->rc);
        node = AVL_rotateLeft(node);
    }
}

void AVL_BalanceForDelete(AVLNode *&node) {
    // 计算平衡因子
    int balance = AVL_getBalanceFactor(node);
    // LL 右旋
    if (balance > 1 && AVL_getBalanceFactor(node->lc) >= 0)
        node = AVL_rotateRight(node);
        // LR 左旋左子树，右旋结点
    else if (balance > 1 && AVL_getBalanceFactor(node->lc) < 0) {
        node->lc = AVL_rotateLeft(node->lc);
        node = AVL_rotateRight(node);
    }
        // RR 左旋
    else if (balance < -1 && AVL_getBalanceFactor(node->rc) <= 0)
        node = AVL_rotateLeft(node);
        // RL 右旋右子树 左旋结点
    else if (balance < -1 && AVL_getBalanceFactor(node->rc) > 0) {
        node->rc = AVL_rotateRight(node->rc);
        node = AVL_rotateLeft(node);
    }
}

/**
 * AVL 插入结点 递归版本
 * @param node
 * @param data
 */
void AVL_InsertNodeRecursive(AVLTree &node, const ElementType &data) {
    if (!node) {
        node = AVL_newNode(data);
    }
    if (data.key < node->data.key) {
        AVL_InsertNodeRecursive(node->lc, data);
    } else if (data.key > node->data.key) {
        AVL_InsertNodeRecursive(node->rc, data);
    } else
        return;
    AVL_UpdateHeight(node);
    AVL_Balance(node);
}

void AVL_InsertNode(AVLTree &tree, const ElementType &data) {
    AVLNode *newNode = AVL_newNode(data);
    if (!tree) {
        tree = newNode;
        return;
    }
    AVLNode *parent = nullptr;
    AVLNode *current = tree;
    stack<AVLNode *> stack;

    while (current) {
        stack.push(current);
        parent = current;
        if (data.key < current->data.key) {
            current = current->lc;
        } else if (data.key > current->data.key) {
            current = current->rc;
        }
    }
    if (parent) {
        if (data.key < parent->data.key)
            parent->lc = newNode;
        else
            parent->rc = newNode;
    }

    while (!stack.empty()) {
        current = stack.top();
        stack.pop();
        AVL_UpdateHeight(current);
        AVL_Balance(current);

        if (!stack.empty()) {
            parent = stack.top();
            if (current->data.key < parent->data.key) {
                parent->lc = current;
            } else {
                parent->rc = current;
            }
        } else {
            tree = current;
        }
    }

}

void AVL_DeleteNodeRecursive(AVLTree &tree, const KeyType &key) {
    if (tree == nullptr) return;
    if (key < tree->data.key)
        AVL_DeleteNodeRecursive(tree->lc, key);
    else if (key > tree->data.key)
        AVL_DeleteNodeRecursive(tree->rc, key);
    else {
        AVLNode *current = tree;
        if (current->lc && current->rc) {
            AVLNode *successor = current->rc;
            while (successor->lc) {
                successor = successor->lc;
            }
            current->data = successor->data;
            AVL_DeleteNodeRecursive(current->rc, successor->data.key);
        } else {
            AVLNode *child = nullptr;
            if (current->lc) {
                child = current->lc;
            } else if (current->rc) {
                child = current->rc;
            }
            if (child == nullptr) {
                child = tree;
                tree = nullptr;
            } else {
                *tree = *child;
            }
            delete child;
        }
    }
    if (tree == nullptr) return;
    AVL_UpdateHeight(tree);
    AVL_BalanceForDelete(tree);
}

void AVL_DeleteNode(AVLTree &tree, const KeyType &key) {
    AVLNode *parent = nullptr;
    AVLNode *current = tree;
    stack<AVLNode *> stack;
    while (current) {
        if (key == current->data.key)
            break;
        parent = current;
        stack.push(parent);
        if (key < current->data.key)
            current = current->lc;
        else if (key > current->data.key)
            current = current->rc;
    }
    if (!current) return;
    if (current->lc && current->rc) {
        AVLNode *successorParent = current;
        AVLNode *successor = current->rc;
        while (successor->lc) {
            successorParent = successor;
            successor = successor->lc;
        }
        if (successor == current->rc) {
            current->rc = successor->rc;
        } else {
            successorParent->lc = successor->rc;
        }
        current->data = successor->data;
        delete successor;
    } else {
        AVLNode *child = nullptr;
        if (current->lc)
            child = current->lc;
        else if (current->rc)
            child = current->rc;
        if (!parent)
            tree = child;
        else if (parent->lc == current)
            parent->lc = child;
        else if (parent->rc == current)
            parent->rc = child;
        delete current;
    }

    while (!stack.empty()) {
        parent = stack.top();
        stack.pop();
        AVL_UpdateHeight(parent);
        AVL_BalanceForDelete(parent);
    }
}


AVLNode *AVL_Search(AVLTree &tree, KeyType key, int *searchCount) {
    AVLNode *current = tree;
    while (current) {
        (*searchCount)++;
        if (current->data.key == key) {
            return current;
        }
        if (key < current->data.key)
            current = current->lc;
        else
            current = current->rc;
    }
    return nullptr;
}

void generateDot(AVLNode *node, ofstream &dotFile) {
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

void generateAVLImage(const AVLTree &tree) {
    ofstream dotFile("avl.dot");
    dotFile << "digraph BinarySearchTree {\n";
    generateDot(tree, dotFile);
    dotFile << "}\n";
    dotFile.close();

    system(R"(C:\Users\zzqni\Downloads\Graphviz-10.0.1-win64\bin\dot.exe -Tpng -o avl.png avl.dot)");
}