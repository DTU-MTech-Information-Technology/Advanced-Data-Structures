#include <bits/stdc++.h>
using namespace std;

struct Node {
    struct Node* left;
    struct Node* right;
    int data;

    Node(int data) {
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

struct Info {
    int max;
    int min;
    bool isBST;
    int sum;
    int currmax;
};

Info MaxSumBSTUtil(struct Node* root, int& maxsum) {
    if (root == NULL) return {INT_MIN, INT_MAX, true, 0, 0};

    if (root->left == NULL && root->right == NULL) {
        maxsum = max(maxsum, root->data);
        return {root->data, root->data, true, root->data, maxsum};
    }

    Info L = MaxSumBSTUtil(root->left, maxsum);
    Info R = MaxSumBSTUtil(root->right, maxsum);
    Info BST;

    if (L.isBST && R.isBST && L.max < root->data && R.min > root->data) {
        BST.max = max(root->data, max(L.max, R.max));
        BST.min = min(root->data, min(L.min, R.min));

        maxsum = max(maxsum, R.sum + root->data + L.sum);
        BST.sum = R.sum + root->data + L.sum;

        BST.currmax = maxsum;

        BST.isBST = true;
        return BST;
    }

    BST.isBST = false;
    BST.currmax = maxsum;
    BST.sum = R.sum + root->data + L.sum;

    return BST;
}

int MaxSumBST(struct Node* root) {
    int maxsum = INT_MIN;
    return MaxSumBSTUtil(root, maxsum).currmax;
}

int main() {
    struct Node* root = new Node(5);
    root->left = new Node(14);
    root->right = new Node(3);
    root->left->left = new Node(6);
    root->right->right = new Node(7);
    root->left->left->left = new Node(9);
    root->left->left->right = new Node(1);

    cout << MaxSumBST(root) << endl;

    return 0;
}
