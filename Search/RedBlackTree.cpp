//
// Created by zzqni on 2024/4/29.
//

#include "RedBlackTree.h"
#include <stack>
#include <fstream>

void RedBlack_Traversal(const RedBlackTree &tree) {
    stack<RBNode *> stack;
    RBNode *current = tree;
    bool first = true;
    printf("RedBlack Tree Traversal Inorder: ");
    while (current || !stack.empty()) {
        if (current) {
            stack.push(current);
            current = current->lc;
        } else {
            RBNode *top = stack.top();
            stack.pop();
            bool print = top->color == RED && top->parent && top->parent->color == RED;
            print = top->color == RED && (top->lc && top->rc == nullptr || top->rc && top->lc == nullptr);
            if (print) {
                if (first) first = false;
                else printf(",");
                printf("%d", top->data.key);
            }
            current = top->rc;
        }
    }
    printf("\n");
}

RBNode *RedBlack_NewNode(RBNode *parent, const ElementType &element) {
    auto node = new RBNode;
    node->data = element;
    node->lc = node->rc = nullptr;
    node->color = RED;
    node->parent = parent;
    return node;
}

void RedBlack_rotateLeft(RedBlackTree &tree, RBNode *node) {
    RBNode *newRoot = node->rc;
    node->rc = newRoot->lc;
    newRoot->lc = node;

    // parent 指针更新
    newRoot->parent = node->parent;
    // node 的 parent 子树更新
    if (node->parent == nullptr)
        // node 为根结点
        tree = newRoot;
    else if (node->parent->lc == node)
        node->parent->lc = newRoot;
    else
        node->parent->rc = newRoot;

    node->parent = newRoot;
    if (node->rc)
        node->rc->parent = node;
}

void RedBlack_rotateRight(RedBlackTree &tree, RBNode *node) {
    RBNode *newRoot = node->lc;
    node->lc = newRoot->rc;
    newRoot->rc = node;

    newRoot->parent = node->parent;
    if (node->parent == nullptr)
        tree = newRoot;
    else if (node->parent->lc == node)
        node->parent->lc = newRoot;
    else
        node->parent->rc = newRoot;

    node->parent = newRoot;
    if (node->lc)
        node->lc->parent = node;
}

void RedBlack_InsertFixUp(RedBlackTree &tree, RBNode *node) {
    // 插入结点的父结点红色时才需要调整
    // 叔叔结点红色时变换颜色，左右相同；
    // 叔叔结点黑色时旋转，左右相反。
    while (node->parent && node->parent->color == RED) {
        // 父结点是祖父结点左孩子
        if (node->parent == node->parent->parent->lc) {
            // LXx
            // 叔叔结点
            RBNode *uncleNode = node->parent->parent->rc;
            // LXr
            // 1. 父节点变黑，叔叔结点变黑，祖父结点变红
            // 2. 当前结点变为祖父结点，向上检查 (祖父的父亲有可能是红色)
            if (uncleNode && uncleNode->color == RED) {
                node->parent->color = BLACK;
                uncleNode->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // LRb
                // 1. node 变成父节点左旋，变LLb
                if (node == node->parent->rc) {
                    node = node->parent;
                    RedBlack_rotateLeft(tree, node);
                }
                // LLb
                // 1. 父节点变为黑色，祖父结点变红
                // 2. 对祖父结点进行右旋。
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RedBlack_rotateRight(tree, node->parent->parent);
                // 旋转后子树的根颜色为黑色，已满足
            }
        } else {
            // 父结点是祖父结点的右孩子
            // RXx
            RBNode *uncleNode = node->parent->parent->lc;
            // Rxr
            // 1. 父节点变黑，叔叔结点变黑，祖父结点变红
            // 2. 当前结点变祖父结点，向上检查
            if (uncleNode && uncleNode->color == RED) {
                node->parent->color = BLACK;
                uncleNode->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                // RLb
                // 1. node 变父结点右旋，变RRb
                if (node == node->parent->lc) {
                    node = node->parent;
                    RedBlack_rotateRight(tree, node);
                }
                // RRb
                // 1. 父结点变黑色，祖父结点变红
                // 2. 对祖父结点进行左旋（对祖父结点来说不满足黑色结点高度相同）
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RedBlack_rotateLeft(tree, node->parent->parent);
                // 旋转后子树的根为黑色，已满足。
            }
        }
    }
    tree->color = BLACK;
}

void RedBlack_InsertNode(RedBlackTree &tree, const ElementType &element) {
    RBNode *parent = nullptr;
    RBNode *current = tree;
    while (current) {
        parent = current;
        if (element.key < current->data.key)
            current = current->lc;
        else
            current = current->rc;
    }
    auto newNode = RedBlack_NewNode(parent, element);
    if (!parent) {
        tree = newNode;
    } else if (element.key < parent->data.key)
        parent->lc = newNode;
    else
        parent->rc = newNode;
    RedBlack_InsertFixUp(tree, newNode);
}

RBNode *RedBlack_GetSuccessor(RBNode *node) {
    RBNode *successor = node->rc;
    while (successor && successor->lc) {
        successor = successor->lc;
    }
    return successor;
}

void RedBlack_DeleteFixup(RedBlackTree &tree, RBNode *x) {
    while (x != tree && (x == nullptr || x->color == BLACK)) {
        if (x && x == x->parent->lc) {
            RBNode *brother = x->parent->rc;
            if (brother->color == RED) {
                brother->color = BLACK;
                x->parent->color = RED;
                RedBlack_rotateLeft(tree, x->parent);
                brother = x->parent->rc;
            }
            if ((brother->lc == nullptr || brother->lc->color == BLACK)
                && (brother->rc == nullptr || brother->rc->color == BLACK)) {
                brother->color = RED;
                x = x->parent;
            } else {
                if (brother->rc == nullptr || brother->rc->color == BLACK) {
                    brother->lc->color = BLACK;
                    brother->color = RED;
                    RedBlack_rotateRight(tree, brother);
                    brother = x->parent->rc;
                }
                brother->color = x->parent->color;
                x->parent->color = BLACK;
                brother->rc->color = BLACK;
                RedBlack_rotateLeft(tree, x->parent);
                x = tree;
            }
        } else {
            RBNode *brother = x->parent->lc;
            if (brother->color == RED) {
                brother->color = BLACK;
                x->parent->color = RED;
                RedBlack_rotateRight(tree, x->parent);
                brother = x->parent->lc;
            }
            if ((brother->rc == nullptr || brother->rc->color == BLACK)
                && (brother->lc == nullptr || brother->lc->color == BLACK)) {
                brother->color = RED;
                x = x->parent;
            } else {
                if (brother->lc == nullptr || brother->lc->color == BLACK) {
                    brother->rc->color = BLACK;
                    brother->color = RED;
                    RedBlack_rotateLeft(tree, brother);
                    brother = x->parent->lc;
                }
                brother->color = x->parent->color;
                x->parent->color = BLACK;
                brother->lc->color = BLACK;
                RedBlack_rotateRight(tree, x->parent);
                x = tree;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

void RedBlack_DeleteNode(RedBlackTree &tree, const KeyType &key) {
    RBNode *current = tree;
    while (current) {
        if (key == current->data.key)
            break;
        else if (key < current->data.key)
            current = current->lc;
        else
            current = current->rc;
    }
    if (current == nullptr) return;
    if (current->lc == nullptr || current->rc == nullptr) {
        RBNode *child = nullptr;
        if (current->lc)
            child = current->lc;
        else if (current->rc)
            child = current->rc;

        if (current == tree)
            tree = child;
        else if (current == current->parent->lc)
            current->parent->lc = child;
        else
            current->parent->rc = child;

        if (child) {
            child->parent = current->parent;
            if (current->color == BLACK)
                RedBlack_DeleteFixup(tree, child);
        }
        delete current;
    } else {
        RBNode *successor = RedBlack_GetSuccessor(current);
        current->data = successor->data;
        if (current->rc == successor) {
            current->rc = successor->rc;
            if (successor->rc)
                successor->rc->parent = current;
        } else {
            successor->parent->lc = successor->rc;
            if (successor->rc)
                successor->rc->parent = successor->parent;
        }

        RBNode *replace = successor->rc;
        if (successor->color == BLACK && replace)
            RedBlack_DeleteFixup(tree, replace);
        delete successor;
    }
}

RBNode *RedBlack_Search(const RedBlackTree &tree, KeyType key, int &searchCount) {
    RBNode *current = tree;
    while (current) {
        searchCount++;
        if (key == current->data.key)
            return current;
        else if (key < current->data.key)
            current = current->lc;
        else
            current = current->rc;
    }
    return nullptr;
}

void generateDot(RBNode *node, ofstream &dotFile) {
    if (node == nullptr) {
        return;
    }

    if (node->color == RED)
        dotFile << "\t" << node->data.key << " [color=red];" << endl;
    else
        dotFile << "\t" << node->data.key << " [color=black];" << endl;

    if (node->lc) {
        dotFile << "\t" << node->data.key << " -> " << node->lc->data.key << " [label=\"L\"];" << endl;
        if (node->lc->color == RED)
            dotFile << "\t" << node->lc->data.key << " [color=red];" << endl;
        else
            dotFile << "\t" << node->lc->data.key << " [color=black];" << endl;
    }
    if (node->rc) {
        dotFile << "\t" << node->data.key << " -> " << node->rc->data.key << " [label=\"R\"];" << endl;
        if (node->rc->color == RED)
            dotFile << "\t" << node->rc->data.key << " [color=red];" << endl;
        else
            dotFile << "\t" << node->rc->data.key << " [color=black];" << endl;
    }

    generateDot(node->lc, dotFile);
    generateDot(node->rc, dotFile);
}

void generateRedBlackTreeImage(const RedBlackTree &tree) {
    ofstream dotFile("blackRedTree.dot");
    dotFile << "digraph RedBlackTree {\n";
    dotFile << "  node [shape=circle];" << endl; // 设置节点形状为圆形
    generateDot(tree, dotFile);
    dotFile << "}\n";
    dotFile.close();

    system(R"(C:\Users\zzqni\Downloads\Graphviz-10.0.1-win64\bin\dot.exe -Tpng -o blackRedTree.png blackRedTree.dot)");
}