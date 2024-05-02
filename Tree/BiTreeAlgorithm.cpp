//
// Created by zzqni on 2024/4/21.
//

#include "BiTreeAlgorithm.h"
#include <vector>

using namespace std;

void testBiTreeAlgorithm() {
//    BiTreePreorderInorder();
}

//preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
BiTree BiTreePreorderInorder(vector<int> &preorder, vector<int> &inorder) {
    if (!preorder.empty()) {
        BiNode *node = new BiNode;
        node->data = preorder[0];
        vector<int> pre(preorder.begin(), preorder.begin() + 1);
    }

}
