#include <bits/stdc++.h>

using namespace std;

struct node {
    int key;
    struct node *left, *right;
    int height;
};

int height(struct node *root) {
    if (root == NULL) return 0;
    return root->height;
}

struct node *create_new_node(int key) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int get_balance(struct node *root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

void preorder(struct node *root) {
    if (root == NULL) return;

    cout << "<key: " << root->key << ", height: " << root->height << ">"
         << endl;
    preorder(root->left);
    preorder(root->right);
}

struct node *insert(struct node *root, int key) {
    if (root == NULL) return create_new_node(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    root->height = 1 + max(height(root->left), height(root->right));
    return root;
}

struct node *right_rotate(struct node *y) {
    struct node *x = y->left;
    struct node *t2 = x->right;

    x->right = y;
    y->left = t2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return x;
}

struct node *left_rotate(struct node *x) {
    struct node *y = x->right;
    struct node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int main(int argc, char const *argv[]) {
    struct node *root = NULL;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 7);

    preorder(root);

    return 0;
}
