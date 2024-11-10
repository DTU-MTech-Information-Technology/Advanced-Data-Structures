#include <iostream>

using namespace std;

class Node {
   public:
    int data;
    Node *left, *right;
    int height;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AVLTree {
   public:
    Node *root;

    AVLTree() { root = NULL; }

    int nodeHeight(Node *node) {
        if (!node) return 0;
        return node->height;
    }

    Node *rightRotate(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;
        y->height = 1 + max(nodeHeight(y->left), nodeHeight(y->right));
        x->height = 1 + max(nodeHeight(x->left), nodeHeight(x->right));

        return x;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;
        x->height = 1 + max(nodeHeight(x->left), nodeHeight(x->right));
        y->height = 1 + max(nodeHeight(y->left), nodeHeight(y->right));

        return y;
    }

    int nodeBalance(Node *node) {
        if (!node) return 0;
        return nodeHeight(node->left) - nodeHeight(node->right);
    }

    Node *insertNode(Node *node, int value) {
        if (!node) return new Node(value);

        if (value < node->data)
            node->left = insertNode(node->left, value);
        else if (value > node->data)
            node->right = insertNode(node->right, value);
        else
            return node;

        node->height = 1 + max(nodeHeight(node->left), nodeHeight(node->right));

        int balance = nodeBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data) return rightRotate(node);

        // Right Right Case
        if (balance < -1 && value > node->right->data) return leftRotate(node);

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insertNode(int value) { root = insertNode(root, value); }

    void preOrder(Node *root) {
        if (root) {
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void preOrder() {
        preOrder(root);
        cout << endl;
    }

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node *deleteNode(Node *root, int value) {
        // standard BST deletion
        if (!root) return root;

        if (value < root->data)
            root->left = deleteNode(root->left, value);

        else if (value > root->data)
            root->right = deleteNode(root->right, value);

        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node *temp = root->left ? root->left : root->right;

                // no child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    // one child case
                    *root = *temp;
                }
                free(temp);
            } else {
                // two children case
                Node *temp = minValueNode(root->right);
                root->data = temp->data;

                // Delete the inorder successor
                root->right = deleteNode(root->right, temp->data);
            }
        }

        // If the tree had only one node then return
        if (!root) return root;

        // AVL balancing
        root->height = 1 + max(nodeHeight(root->left), nodeHeight(root->right));
        int balance = nodeBalance(root);

        // Left Left Case
        if (balance > 1 && nodeBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && nodeBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && nodeBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && nodeBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteNode(int value) { root = deleteNode(root, value); }
};

int main(int argc, char const *argv[]) {
    AVLTree tree;

    tree.insertNode(10);
    tree.insertNode(20);
    tree.insertNode(30);
    tree.insertNode(40);
    tree.insertNode(50);
    tree.insertNode(25);

    tree.preOrder();

    tree.deleteNode(40);
    tree.deleteNode(50);

    tree.preOrder();

    return 0;
}
