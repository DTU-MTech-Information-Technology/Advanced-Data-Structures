#include <iostream>
#include <queue>

using namespace std;

class Node {
   public:
    int data;
    Node *left, *right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class CompleteBinaryTree {
   public:
    Node *root;

    CompleteBinaryTree() { root = NULL; }

    void insert(int value) {
        if (!root) {
            root = new Node(value);
            return;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            Node *current = q.front();
            q.pop();

            if (!current->left) {
                current->left = new Node(value);
                break;
            } else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = new Node(value);
                break;
            } else {
                q.push(current->right);
            }
        }
    }

    int count(Node *root) {
        if (!root) return 0;
        return 1 + count(root->left) + count(root->right);
    }

    int count() { return count(root); }
};

int main(int argc, char const *argv[]) {
    CompleteBinaryTree tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    cout << "Number of nodes: " << tree.count() << endl;

    return 0;
}
